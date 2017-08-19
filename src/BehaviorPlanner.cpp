//
// Created by ks on 07.08.17.
//

#include <algorithm>
#include "BehaviorPlanner.h"


//BehaviorPlanner::BehaviorPlanner(int lane,double s, double d, double v, double a): currentLane(lane),s(s),v(v),a(a),currentState("KL") {}

BehaviorPlanner::BehaviorPlanner(): current_state("KL"){}

BehaviorPlanner::~BehaviorPlanner(){}

vector<string> BehaviorPlanner::get_successor_states(Car &car) {

    vector<string> successorStates;

    if (car.current_state.compare("KL") == 0) {
        successorStates.push_back("KL");
        successorStates.push_back("LCL");
        successorStates.push_back("LCR");
    }

    else if (car.current_state.compare("LCL") == 0) {
        successorStates.push_back("KL");
    }

    else if (car.current_state.compare("LCR") == 0) {
        successorStates.push_back("KL");
    }

    if (car.current_lane == 0) {
        successorStates.erase(std::remove(successorStates.begin(), successorStates.end(), "LCL"), successorStates.end());
    }

    if (car.current_lane == 2) {
        successorStates.erase(std::remove(successorStates.begin(), successorStates.end(), "LCR"), successorStates.end());
    }

    return successorStates;
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
