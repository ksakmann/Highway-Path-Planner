//
// Created by ks on 12.08.17.
//

#ifndef PATH_PLANNING_PATH_H
#define PATH_PLANNING_PATH_H

#include <vector>

using namespace std;

class Path {

public:

    vector<double> x;
    vector<double> y;
    int target_lane;
    double v;
    double cost;


    Path();
    Path(vector<double> x_,vector<double> y_,double v_);
    void compute_cost();


    double evaluate_distance();
};


#endif //PATH_PLANNING_PATH_H
