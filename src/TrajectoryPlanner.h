//
// Created by ks on 12.08.17.
//

#ifndef PATH_PLANNING_TRAJECTORYPLANNER_H
#define PATH_PLANNING_TRAJECTORYPLANNER_H


#include "Waypoints.h"
#include "Car.h"
#include "Path.h"
#include "Helper.h"

class TrajectoryPlanner {

public:

    Waypoints waypoints;
    double vref;
    double v_prev;

    double pos_x;
    double pos_y;
    double pos_s;
    double pos_d;
    double angle;
    double end_path_s;
    double end_path_d;
    bool start_from_scratch = false;

    vector<double> previous_path_x;
    vector<double> previous_path_y;
    vector<double> base_nodes_y;
    vector<double> nodes_x;
    vector<double> base_nodes_x;
    vector<double> nodes_y;
    int prev_size;


    vector<vector<double>> sensor_fusion;
    Car car;
    vector<Path> paths;

    int current_lane;
    bool current_lane_busy;
    double speed_ahead;
    vector<int> free_lanes;
    vector<int> lanes;

    TrajectoryPlanner(Waypoints wp, double vref_);

    void update(vector<double> previous_path_x_, vector<double> previous_path_y_, double end_path_s_,
                double end_path_d_, vector<vector<double>> sensor_fusion_, Car car_);

    void generate_base_nodes();

    void shift_and_rotate_nodes();

    void update_lanes_status();

    void get_v_prev();

    Path generate_path(int target_lane, double target_v, double target_x_prime);

    void generate_paths();


private:
    void generate_nodes(int target_lane);


};


#endif //PATH_PLANNING_TRAJECTORYPLANNER_H
