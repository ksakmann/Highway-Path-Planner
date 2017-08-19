//
// Created by ks on 07.08.17.
//

#include <algorithm>
#include <iostream>
#include "BehaviorPlanner.h"


BehaviorPlanner::BehaviorPlanner() {}

BehaviorPlanner::~BehaviorPlanner(){}

vector<Car::State> BehaviorPlanner::get_successor_states(Car &car) {

    vector<Car::State> successor_states;
    auto current = car.current_state;
    current.target_lane = car.current_lane;

    successor_states.push_back(current);

    if (current.state.compare("KL") == 0) {

        if (car.current_lane == 0) {

            Car::State LCR = {.state = "LCR", .target_lane = 1};
            successor_states.push_back(LCR);
        }

        if (car.current_lane == 1) {

            Car::State LCR = {.state = "LCR", .target_lane = 2};
            successor_states.push_back(LCR);

            Car::State LCL = {.state = "LCL", .target_lane = 0};
            successor_states.push_back(LCL);
        }

        if (car.current_lane == 2) {

            Car::State LCL = {.state = "LCL", .target_lane = 1};
            successor_states.push_back(LCL);
        }

    }

    return successor_states;
}


void BehaviorPlanner::update(Car &car) {

    if (car.last_maneuver_completed()) {
        car.successor_states = get_successor_states(car);
    }
    else
    {
        car.successor_states.clear();
        car.successor_states.push_back(car.current_state);
    }

}
