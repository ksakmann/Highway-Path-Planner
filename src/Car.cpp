//
// Created by ks on 08.08.17.
//

#include <cmath>
#include <deque>
#include <assert.h>
#include <iostream>
#include "Car.h"

Car::Car() {

    current_state.state = "KL";
    current_state.target_lane = 1;

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
    current_lane = get_lane(d);
    last_d_vals.push_front(d);
    while (last_d_vals.size() > 50){
        last_d_vals.pop_back();
    }
    maneuver_completed = last_maneuver_completed();

}

int Car::get_lane(double d) {

    double lane_width = 4.0;
    return int(floor(d/lane_width));

}

bool Car::last_maneuver_completed() {

    bool maneuver_completed = false;
    double d_avg = 0;

    if (current_state.state == "KL") {
        maneuver_completed = true;
    }
    else {
        for (auto d_val : last_d_vals){
            d_avg += d_val;
        }
        assert(last_d_vals.size() > 0);
        d_avg /= last_d_vals.size();
        cout << " DEBUG " << d_avg << " " << " get_lane(d_avg)" << endl;
        if (get_lane(d_avg) == current_state.target_lane){
            maneuver_completed = true;
            current_state.state = "KL";
            current_state.target_lane = current_lane;
        }
    }

    return maneuver_completed;
}

void Car::info() {

    cout << "current_lane                " << current_lane  << " " << endl;
    cout << "current_state.target_lane   " << current_state.target_lane << " " << endl;
    cout << "current_state.state         " << current_state.state << " " << endl;
    cout << "successor_states " ;
    for (auto state : successor_states) {
        cout <<  state.state << " " << state.target_lane << " ";
    }
    cout << endl;
    cout << "maneouver_completed " << maneuver_completed << endl;
}


