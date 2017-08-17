//
// Created by ks on 08.08.17.
//

#include <cmath>
#include "Car.h"

Car::Car(string current_state_) : current_state(current_state_) {

    successor_states.push_back("KL");
}

Car::~Car() {

}

void Car::update(double x_in, double y_in, double s_in, double d_in, double yaw_in, double speed_in) {

    x = x_in;
    y = y_in;
    s = s_in;
    d = d_in;
    yaw = yaw_in;
    speed = speed_in;
    get_lane();

}

void Car::get_lane() {

    double lane_width = 4.0;
    current_lane = int(floor(d/lane_width));

}


