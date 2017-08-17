//
// Created by ks on 08.08.17.
//

#ifndef PATH_PLANNING_CAR_H
#define PATH_PLANNING_CAR_H

#include <string>
#include <vector>

using namespace std;

class Car {
public:
    double x;
    double y;
    double s;
    double d;
    double yaw;
    double speed;

    int current_lane;
    int target_lane;

    string current_state;
    vector<string> successor_states;

    Car(string current_state_);
    ~Car();
    void update(double x,double y,double s,double d,double yaw,double speed);
    void get_lane();

};


#endif //PATH_PLANNING_CAR_H
