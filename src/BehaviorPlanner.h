//
// Created by ks on 07.08.17.
//

#ifndef BEHAVIOR_PLANNER_H
#define BEHAVIOR_PLANNER_H

#include "Car.h"

using namespace std;

class BehaviorPlanner {
public:


    BehaviorPlanner();
    ~BehaviorPlanner();

    vector<Car::State> get_successor_states(Car &car);
    void update(Car &car);

};


#endif //BEHAVIOR_PLANNER_H
