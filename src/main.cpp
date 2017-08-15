#include <fstream>
#include <math.h>
#include <uWS/uWS.h>
#include <chrono>
#include <iostream>
#include <thread>
#include <vector>
#include "Eigen-3.3/Eigen/Core"
#include "Eigen-3.3/Eigen/QR"
#include "json.hpp"
#include "Waypoints.h"
//#include "Path.h"
#include "BehaviorPlanner.h"
#include "TrajectoryPlanner.h"
#include "Car.h"
#include "Helper.h"

using namespace std;

// for convenience
using json = nlohmann::json;

int main() {
    uWS::Hub h;

    // Load up map values for waypoint's x,y,s and d normalized normal vectors
    vector<double> map_waypoints_x;
    vector<double> map_waypoints_y;
    vector<double> map_waypoints_s;
    vector<double> map_waypoints_dx;
    vector<double> map_waypoints_dy;

    // Waypoint map to read from
    string map_file_ = "../data/highway_map.csv";
    // The max s value before wrapping around the track back to 0
    double max_s = 6945.554;

    ifstream in_map_(map_file_.c_str(), ifstream::in);

    string line;
    while (getline(in_map_, line)) {
        istringstream iss(line);
        double x;
        double y;
        double s;
        double d_x;
        double d_y;
        iss >> x;
        iss >> y;
        iss >> s;
        iss >> d_x;
        iss >> d_y;
        map_waypoints_x.push_back(x);
        map_waypoints_y.push_back(y);
        map_waypoints_s.push_back(s);
        map_waypoints_dx.push_back(d_x);
        map_waypoints_dy.push_back(d_y);

    }

    // wrap the waypoints in a class and do the interpolation

    Waypoints waypoints(map_waypoints_x, map_waypoints_y, map_waypoints_s, map_waypoints_dx, map_waypoints_dy);
    TrajectoryPlanner trajectoryPlanner(waypoints,0.0);
    BehaviorPlanner planner;
    Car car;

    h.onMessage([&waypoints, &planner, &car, &trajectoryPlanner](uWS::WebSocket<uWS::SERVER> ws, char *data, size_t length,
                             uWS::OpCode opCode) {
        // "42" at the start of the message means there's a websocket message event.
        // The 4 signifies a websocket message
        // The 2 signifies a websocket event
        //auto sdata = string(data).substr(0, length);
        //cout << sdata << endl;
        if (length && length > 2 && data[0] == '4' && data[1] == '2') {

            auto s = hasData(data);

            if (s != "") {
                auto j = json::parse(s);

                string event = j[0].get<string>();

                if (event == "telemetry") {
                    // j[1] is the data JSON object

                    // update the car
                    car.update(j[1]["x"], j[1]["y"], j[1]["s"], j[1]["d"], j[1]["yaw"], j[1]["speed"]);

                    // Previous path data given to the planner
                    auto previous_path_x = j[1]["previous_path_x"];
                    auto previous_path_y = j[1]["previous_path_y"];

                    // Previous path's end s and d values
                    double end_path_s = j[1]["end_path_s"];
                    double end_path_d = j[1]["end_path_d"];

                    // Sensor Fusion Data, a list of all other cars on the same side of the road.
                    auto sensor_fusion = j[1]["sensor_fusion"];

                    json msgJson;

                    vector<double> next_x_vals;
                    vector<double> next_y_vals;


                    // TODO:
                    // We will use a finite currentState machine as a behaviour planner for the car
                    // 1. get currentState of the car
                    // planner.update_vehicleState();
                    // 2. determine possible actions allowed by the finite currentState machine
                    vector<string> successorStates = planner.get_successorStates();
                    // 3. for any possible action generate sample paths (do not worry about collisions yet)
                    //     BUT make sure they are jerk minimal for different boundary conditions.
                    // 4. evaluate feasibility of sampled paths (collisions, speed limits)
                    // 5. determine cost of feasible path: speed, jerk, cost of changing trajectory
                    // 6. pass path to simulator

                    vector<double> nodes_x;
                    vector<double> nodes_y;

                    double pos_x;
                    double pos_y;
                    double pos_s;
                    double pos_d;
                    double angle;
                    int prev_size = previous_path_x.size();

                    trajectoryPlanner.update(previous_path_x, previous_path_y, end_path_s, end_path_d, sensor_fusion,
                                             car);
                    trajectoryPlanner.generate_base_nodes();

                    nodes_x = trajectoryPlanner.base_nodes_x;
                    nodes_y = trajectoryPlanner.base_nodes_y;
                    angle = trajectoryPlanner.angle;
                    pos_x = trajectoryPlanner.pos_x;
                    pos_y = trajectoryPlanner.pos_y;
                    pos_s = trajectoryPlanner.pos_s;
                    pos_d = trajectoryPlanner.pos_d;

                    trajectoryPlanner.update_lanes_status();
                    trajectoryPlanner.generate_paths();

                    vector<int> lanes = trajectoryPlanner.lanes;



                    next_x_vals = trajectoryPlanner.paths[0].x;
                    next_y_vals = trajectoryPlanner.paths[0].y;

                    msgJson["next_x"] = next_x_vals;
                    msgJson["next_y"] = next_y_vals;

                    auto msg = "42[\"control\"," + msgJson.dump() + "]";

                    //this_thread::sleep_for(chrono::milliseconds(1000));
                    ws.send(msg.data(), msg.length(), uWS::OpCode::TEXT);

                }
            } else {
                // Manual driving
                std::string msg = "42[\"manual\",{}]";
                ws.send(msg.data(), msg.length(), uWS::OpCode::TEXT);
            }
        }
    });

    // We don't need this since we're not using HTTP but if it's removed the
    // program
    // doesn't compile :-(
    h.onHttpRequest([](uWS::HttpResponse *res, uWS::HttpRequest req, char *data,
                       size_t, size_t) {
        const std::string s = "<h1>Hello world!</h1>";
        if (req.getUrl().valueLength == 1) {
            res->end(s.data(), s.length());
        } else {
            // i guess this should be done more gracefully?
            res->end(nullptr, 0);
        }
    });

    h.onConnection([&h](uWS::WebSocket<uWS::SERVER> ws, uWS::HttpRequest req) {
        std::cout << "Connected!!!" << std::endl;
    });

    h.onDisconnection([&h](uWS::WebSocket<uWS::SERVER> ws, int code,
                           char *message, size_t length) {
        ws.close();
        std::cout << "Disconnected" << std::endl;
    });

    int port = 4567;
    if (h.listen(port)) {
        std::cout << "Listening to port " << port << std::endl;
    } else {
        std::cerr << "Failed to listen to port" << std::endl;
        return -1;
    }
    h.run();
}
















































































