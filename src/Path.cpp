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

    cost = velocity_cost + lane_cost + collision_cost;


}

double Path::evaluate_collision_cost(const vector<vector<double>> & sensor_fusion){

    bool will_collide = false;

    /*
    for (int i = 0; i < sensor_fusion.size(); i++) {


        double d = sensor_fusion[i][6];

        if ((d < 2 + lane * 4 + 2) && (d > 2 + lane * 4 - 2)) {
            double vx = sensor_fusion[i][3];
            double vy = sensor_fusion[i][4];
            double check_speed = sqrt(vx * vx + vy * vy);
            double check_car_s = sensor_fusion[i][5];

            check_car_s += (prev_size * 0.02 * check_speed);

            if (lane == current_lane) {
                if ((check_car_s > pos_s) && (check_car_s - pos_s < 30)) {
                    lanes[lane] = 1;
                    current_lane_busy = true;
                    speed_ahead[lane] = check_speed;
                }
            }

            else {
                if (fabs(pos_s - check_car_s) < 30) {
                    lanes[lane] = 1;
                    speed_ahead[lane] = check_speed;
                }
            }
        }

    }
   */
    return 0;

}


