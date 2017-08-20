//
// Created by ks on 12.08.17.
//

#ifndef PATH_PLANNING_PATH_H
#define PATH_PLANNING_PATH_H

#include <vector>
#include "Car.h"

using namespace std;

class Path {

public:

    vector<double> x;
    vector<double> y;

    Car::State state;
    double v;
    vector<int> lanes;
    double cost;

    Path();
    Path(vector<double> x_,vector<double> y_,double v_);
    void compute_cost(const vector<vector<double>> & sensor_fusion);
    double evaluate_collision_cost(const vector<vector<double>> & sensor_fusion);
};


#endif //PATH_PLANNING_PATH_H
