//
// Created by ks on 07.08.17.
//

#ifndef BEHAVIOR_PLANNER_H
#define BEHAVIOR_PLANNER_H

using namespace std;

class BehaviorPlanner {
public:

    int currentLane;
    int nextLane;
    double s;
    double d;
    double v;
    double a;
    string currentState;
    string nextState;

    //BehaviorPlanner(int lane,double s, double d, double v, double a);
    BehaviorPlanner();
    ~BehaviorPlanner();

    vector<string> get_successorStates();
    int get_lane();

};


#endif //BEHAVIOR_PLANNER_H
