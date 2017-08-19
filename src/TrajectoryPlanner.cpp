//
// Created by ks on 12.08.17.
//

#include <iostream>
#include "TrajectoryPlanner.h"

TrajectoryPlanner::TrajectoryPlanner(Waypoints wp, double vref_, int horizon_) : waypoints(wp), vref(vref_), horizon(horizon_),
                                                                                 car(std::__cxx11::string()) {

}


void TrajectoryPlanner::update(vector<double> previous_path_x_, vector<double> previous_path_y_, double end_path_s_, double end_path_d_, vector<vector<double>> sensor_fusion_, Car car_) {

    car = car_;
    previous_path_x = previous_path_x_;
    previous_path_y = previous_path_y_;
    pos_x = car.x;
    pos_y = car.y;
    pos_s = car.s;
    pos_d = car.d;
    sensor_fusion = sensor_fusion_;
    assert (previous_path_x_.size() == previous_path_y_.size());
    prev_size = static_cast<int>(previous_path_x.size());
    current_lane = car.current_lane;
    end_path_s = end_path_s_;
    end_path_d = end_path_d_;

}

void TrajectoryPlanner::generate_base_nodes()  {

    base_nodes_x.clear();
    base_nodes_y.clear();

    if ((prev_size < 2) || start_from_scratch ) {
        pos_x = car.x;
        pos_y = car.y;
        pos_s = car.s;
        pos_d = car.d;
        angle = deg2rad(car.yaw);
        double prev_x = car.x - cos(angle);
        double prev_y = car.y - sin(angle);

        base_nodes_x.push_back(prev_x);
        base_nodes_x.push_back(pos_x);
        base_nodes_y.push_back(prev_y);
        base_nodes_y.push_back(pos_y);

    }
    else {
        pos_x = previous_path_x[prev_size - 1];
        pos_y = previous_path_y[prev_size - 1];
        pos_s = end_path_s;
        pos_d = end_path_d;

        double pos_x2 = previous_path_x[prev_size - 2];
        double pos_y2 = previous_path_y[prev_size - 2];
        angle = atan2(pos_y - pos_y2, pos_x - pos_x2);

        base_nodes_x.push_back(pos_x2);
        base_nodes_x.push_back(pos_x);
        base_nodes_y.push_back(pos_y2);
        base_nodes_y.push_back(pos_y);

    }
}

void TrajectoryPlanner::generate_nodes(int target_lane,double delta_s) {

    nodes_x = base_nodes_x;
    nodes_y = base_nodes_y;

    vector <double> wp0 = waypoints.get_X(pos_s + 1*delta_s, 2 + target_lane * 4);
    vector <double> wp1 = waypoints.get_X(pos_s + 2*delta_s, 2 + target_lane * 4);
    vector <double> wp2 = waypoints.get_X(pos_s + 3*delta_s, 2 + target_lane * 4);

    nodes_x.push_back(wp0[0]);
    nodes_x.push_back(wp1[0]);
    nodes_x.push_back(wp2[0]);

    nodes_y.push_back(wp0[1]);
    nodes_y.push_back(wp1[1]);
    nodes_y.push_back(wp2[1]);

}

Path TrajectoryPlanner::generate_path(int target_lane, double target_v, double target_x_prime) {

    Path path;
    path.target_lane = target_lane;
    path.v = target_v;

    if ((!start_from_scratch) && prev_size > 0) {
        // use previous path points here for a smooth trajectory.
        path.x = previous_path_x;
        path.y = previous_path_y;
    }

    // make sure that the speeds match and that accelerations are bounded.
    get_v_prev(); // get the previous speed at the end of the trajectory

    double delta_prev = v_prev * 0.02 / 2.24;
    double a_max = 5; // 5m/s**2
    double delta_max = delta_prev + 0.02*0.02 * a_max;
    double delta_min = delta_prev - 0.02*0.02 * a_max;
    double delta_used;
    double delta_s = 40;

    generate_nodes(target_lane,delta_s);
    shift_and_rotate_nodes(); // aligns the vehicle direction with the x-axis.

    tk::spline spline_xy_prime;
    spline_xy_prime.set_points(nodes_x,nodes_y);

    double target_y_prime = spline_xy_prime(target_x_prime);
    double target_distance = sqrt(target_x_prime*target_x_prime + target_y_prime* target_y_prime);
    double x_add_on = 0;


    for (int i = 0 ; i <  horizon - prev_size ; i++ ){
        double N = target_distance / (0.02 * target_v / 2.24);
        //cout << "target_x_prime / N " << target_x_prime / N << " delta_max " << delta_max << " delta_prev " << delta_prev << endl;


        if (target_v > v_prev) {
            delta_used = min(target_x_prime / N,delta_max);
        } else {
            delta_used = max(target_x_prime / N,delta_min);
        }

        double x_point = x_add_on + delta_used;
        double y_point = spline_xy_prime(x_point);

        x_add_on = x_point;

        double x_  =  x_point;
        double y_  =  y_point;

        x_point =  cos(angle) * x_ - sin(angle) * y_ ;
        y_point =  sin(angle) * x_ + cos(angle) * y_ ;

        x_point +=  pos_x;
        y_point +=  pos_y;

        path.x.push_back(x_point);
        path.y.push_back(y_point);

    }

    path.compute_cost();

    return path;
}

void TrajectoryPlanner::shift_and_rotate_nodes() {

    assert (nodes_x.size() == nodes_y.size());
    for (auto i = 0 ; i < nodes_x.size() ; ++i) {

        double x_ =  nodes_x[i] - pos_x;
        double y_ =  nodes_y[i] - pos_y;
        nodes_x[i]  = cos(angle) * x_ + sin(angle) * y_;
        nodes_y[i]  = - sin(angle) * x_ + cos(angle) * y_;
    }
}


void TrajectoryPlanner::update_lanes_status() {

    current_lane_busy = false;
    lanes = {0,0,0};

    for (auto lane = 0 ; lane < lanes.size(); lane++ ) {
        for (int i = 0; i < sensor_fusion.size(); i++) {

            double d = sensor_fusion[i][6];

            if ((d < 2 + lane * 4 + 2) && (d > 2 + lane * 4 - 2)) {
                double vx = sensor_fusion[i][3];
                double vy = sensor_fusion[i][4];
                double check_speed = sqrt(vx * vx + vy * vy);
                double check_car_s = sensor_fusion[i][5];

                check_car_s += (prev_size * 0.02 * check_speed);

                if (lane == current_lane) {
                    speed_ahead = 0;
                    if ((check_car_s > pos_s) && (check_car_s - pos_s < 30)) {
                        lanes[lane] = 1;
                        current_lane_busy = true;
                        speed_ahead = check_speed;
                    }
                }

                else {
                    if (fabs(pos_s - check_car_s) < 25) {
                        lanes[lane] = 1;
                    }
                }
            }
        }
    }


    free_lanes.clear();
    for (int i = 0 ; i < lanes.size() ; i++){
        if(lanes[i] == 0){
            free_lanes.push_back(i);
        }
    }


}

void TrajectoryPlanner::generate_paths() {

    paths.clear();
    update_lanes_status();



    if (free_lanes.size()==0){
        get_v_prev();
        double target_v = speed_ahead;

        Path path = generate_path(current_lane,target_v,30.0);
        paths.push_back(path);
    }

    else

    {
        if (vref < 49.5) {
            vref += 0.224;
        }

        for (auto i = 0 ; i < lanes.size(); i++){
            if (lanes[i] == 0){
                Path path = generate_path(i,vref,30.0);
                paths.push_back(path);

            }
        }

    }
 /***
    if (free_lanes.size() == 0){
        get_v_prev();
        double target_v = speed_ahead;

        Path path = generate_path(current_lane,target_v,30.0);
        paths.push_back(path);
    }

    else

    {
        if (vref < 49.5) {
            vref = 49.5;
        }


        for (auto successor_state : car.successor_states){

            int target_lane;
            if (successor_state.compare("KL") == 0 ) {
                target_lane = car.current_lane;
            }
            else if (successor_state.compare("LCL") == 0 ) {
                target_lane = car.current_lane - 1 ;
            }
            else if (successor_state.compare("LCR") == 0 ) {
                target_lane = car.current_lane + 1 ;

            }
            Path path = generate_path(target_lane, vref, 30.0);
            paths.push_back(path);

        }


    }
    ***/

}

void TrajectoryPlanner::get_v_prev() {
    if (prev_size >1){
        double x0 = previous_path_x[prev_size-2];
        double x1 = previous_path_x[prev_size-1];
        double y0 = previous_path_y[prev_size-2];
        double y1 = previous_path_y[prev_size-1];

        v_prev = sqrt((x1-x0)*(x1-x0) + (y1-y0)*(y1-y0)) / 0.02 * 2.24 ;

    }
    else {
        v_prev = car.speed;
    }

}


