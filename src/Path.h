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

    Path();
    Path(vector<double> x_,vector<double> y_);

};


#endif //PATH_PLANNING_PATH_H
