//
// Created by ks on 07.08.17.
//

#include <algorithm>
#include "BehaviorPlanner.h"


BehaviorPlanner::BehaviorPlanner(int lane,double s, double d, double v, double a): lane(lane),s(s),v(v),a(a),state("KL") {}

BehaviorPlanner::BehaviorPlanner(): state("KL") {}


vector<string> BehaviorPlanner::get_successorStates() {

    vector<string> successorStates;

    if (state.compare("KL") == 0) {
        successorStates.push_back("KL");
        successorStates.push_back("PLCL");
        successorStates.push_back("PLCR");
    }

    else if (state.compare("PLCL") == 0) {
        successorStates.push_back("KL");
        successorStates.push_back("PLCL");
        successorStates.push_back("LCL");
    }

    else if (state.compare("PLCR") == 0) {
        successorStates.push_back("KL");
        successorStates.push_back("PLCR");
        successorStates.push_back("LCR");
    }

    else if (state == "LCL") {
        successorStates.push_back("KL");
    }

    else if (state.compare("LCR") == 0) {
        successorStates.push_back("KL");
    }

    if (this->lane == 0) {
        successorStates.erase(std::remove(successorStates.begin(), successorStates.end(), "PLCR"), successorStates.end());
    }

    if (this->lane == 3) {
        successorStates.erase(std::remove(successorStates.begin(), successorStates.end(), "PLCL"), successorStates.end());
    }

    return successorStates;
}

BehaviorPlanner::~BehaviorPlanner(){};
