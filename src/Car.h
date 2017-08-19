//
// Created by ks on 08.08.17.
//

#ifndef PATH_PLANNING_CAR_H
#define PATH_PLANNING_CAR_H

#include <string>
#include <vector>
#include <deque>

using namespace std;

class Car {
public:
    double x;
    double y;
    double s;
    double d;
    double yaw;
    double speed;
    deque<double> last_d_vals;

    int current_lane;
    bool maneuver_completed;

    struct State {
        string state;
        int target_lane;
    };


    State current_state;
    vector<State> successor_states;

    Car();
    ~Car();
    void update(double x,double y,double s,double d,double yaw,double speed);
    int get_lane(double d);
    bool last_maneuver_completed();

    void info();

};


#endif //PATH_PLANNING_CAR_H
