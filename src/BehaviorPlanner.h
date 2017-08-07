//
// Created by ks on 07.08.17.
//

#ifndef BEHAVIOR_PLANNER_H
#define BEHAVIOR_PLANNER_H

using namespace std;

class BehaviorPlanner {
public:

    int lane;
    double s;
    double v;
    double a;
    string state;

    BehaviorPlanner(int lane,double s, double d, double v, double a);
    BehaviorPlanner();
    ~BehaviorPlanner();

    vector<string> get_successorStates();

};


#endif //BEHAVIOR_PLANNER_H
