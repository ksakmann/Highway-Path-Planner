//
// Created by ks on 07.08.17.
//

#include <algorithm>
#include "BehaviorPlanner.h"


//BehaviorPlanner::BehaviorPlanner(int lane,double s, double d, double v, double a): currentLane(lane),s(s),v(v),a(a),currentState("KL") {}

BehaviorPlanner::BehaviorPlanner(): current_state("KL"){}


vector<string> BehaviorPlanner::get_successor_states() {

    vector<string> successorStates;

    if (current_state.compare("KL") == 0) {
        successorStates.push_back("KL");
        successorStates.push_back("LCL");
        successorStates.push_back("LCR");
    }

    else if (current_state.compare("LCL") == 0) {
        successorStates.push_back("KL");
    }

    else if (current_state.compare("LCR") == 0) {
        successorStates.push_back("KL");
    }

    if (current_lane == 0) {
        successorStates.erase(std::remove(successorStates.begin(), successorStates.end(), "LCL"), successorStates.end());
    }

    if (current_lane == 2) {
        successorStates.erase(std::remove(successorStates.begin(), successorStates.end(), "LCR"), successorStates.end());
    }

    return successorStates;
}

BehaviorPlanner::~BehaviorPlanner(){}


void BehaviorPlanner::update(Car &car) {

    successor_states = get_successor_states();

}
