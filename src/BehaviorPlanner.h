//
// Created by ks on 07.08.17.
//

#ifndef BEHAVIOR_PLANNER_H
#define BEHAVIOR_PLANNER_H

#include "Car.h"

using namespace std;

class BehaviorPlanner {
public:

    int current_lane;
    int target_lane;
    double time_in_target_lane = 0;
    string current_state;
    vector<string> successor_states;

    BehaviorPlanner();
    ~BehaviorPlanner();

    vector<string> get_successor_states();
    void update(Car &car);

};


#endif //BEHAVIOR_PLANNER_H
