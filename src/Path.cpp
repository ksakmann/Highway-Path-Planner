//
// Created by ks on 12.08.17.
//

#include <cmath>
#include "Path.h"

Path::Path() {

}

Path::Path(vector<double> x_, vector<double> y_,double v_) : x(x_),y(y_),v(v_) {

}

void Path::compute_cost(const vector<vector<double>> & sensor_fusion) {

    double vmax = 49.5;
    double velocity_cost = fabs((vmax-v)/vmax); // penalizes deviations from the maximum speed
    double collision_cost = evaluate_collision_cost(sensor_fusion);
    double lane_cost = state.target_lane*0.05 + 2*lanes[state.target_lane]; // this favors the left lane in case of splits, otherwise empty lanes
    double lane_change_cost = pow((state.target_lane-state.start_lane),2)*lanes[state.target_lane];

    cost = velocity_cost + lane_cost + lane_change_cost + collision_cost;


}

//TODO: currently collisions are avoided by not changing lanes when they are busy. Collisions should be evaluated for each path.
double Path::evaluate_collision_cost(const vector<vector<double>> &sensor_fusion) {
    return 0;
}


