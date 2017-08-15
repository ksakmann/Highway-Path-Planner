//
// Created by ks on 07.08.17.
//

#include <algorithm>
#include "BehaviorPlanner.h"


//BehaviorPlanner::BehaviorPlanner(int lane,double s, double d, double v, double a): currentLane(lane),s(s),v(v),a(a),currentState("KL") {}

BehaviorPlanner::BehaviorPlanner(): currentState("KL"), nextState("KL"){}


vector<string> BehaviorPlanner::get_successorStates() {

    vector<string> successorStates;

    if (currentState.compare("KL") == 0) {
        successorStates.push_back("KL");
        successorStates.push_back("PLCL");
        successorStates.push_back("PLCR");
    }

    else if (currentState.compare("PLCL") == 0) {
        successorStates.push_back("KL");
        successorStates.push_back("PLCL");
        successorStates.push_back("LCL");
    }

    else if (currentState.compare("PLCR") == 0) {
        successorStates.push_back("KL");
        successorStates.push_back("PLCR");
        successorStates.push_back("LCR");
    }

    else if (currentState == "LCL") {
        successorStates.push_back("KL");
    }

    else if (currentState.compare("LCR") == 0) {
        successorStates.push_back("KL");
    }

    if (currentLane == 0) {
        successorStates.erase(std::remove(successorStates.begin(), successorStates.end(), "PLCR"), successorStates.end());
    }

    if (currentLane == 3) {
        successorStates.erase(std::remove(successorStates.begin(), successorStates.end(), "PLCL"), successorStates.end());
    }

    return successorStates;
}

BehaviorPlanner::~BehaviorPlanner(){}

int BehaviorPlanner::get_lane() {
    double laneWidth = 4.0;
    int lane = int(floor(d/laneWidth));
    return lane;
};
