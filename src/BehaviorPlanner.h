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
    string current_state;

    BehaviorPlanner();
    ~BehaviorPlanner();

    vector<string> get_successor_states(Car &car);
    void update(Car &car);

};


#endif //BEHAVIOR_PLANNER_H
