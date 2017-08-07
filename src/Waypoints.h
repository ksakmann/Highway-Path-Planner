#ifndef WAYPOINTS_H
#define WAYPOINTS_H

#include <vector>
#include "spline.h"

using std::vector;

class Waypoints {

public:
    Waypoints(vector<double> x, vector<double> y, vector<double> s, vector<double> d_x, vector<double> d_y);

    ~Waypoints() {};

    vector<double> x_;
    vector<double> y_;
    vector<double> s_;
    vector<double> d_x_;
    vector<double> d_y_;

    tk::spline sx, sy, snx, sny;

    // get interpolated map coordinates and normal vector given Frenet s
    vector<double> get_X(double s, double d);

    void fit_splines();

};

#endif
