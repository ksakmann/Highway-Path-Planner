#ifndef PATH_H
#define PATH_H

#include <vector>
#include "spline.h"

using std::vector;

class Path {

public:

    vector<double> time;
    vector<double> velocity;

    vector<double> X_;
    vector<double> Y_;
    vector<double> pathDistance;

    tk::spline sx, sy;

    double pathLength;

    vector<double> X;
    vector<double> Y;

    Path(vector<double> X_in, vector<double> Y_in, double distInc);

    ~Path();

private:

    void get_pathDistance();

    void fit_splines();

    void get_interpolatedPath(double distInc);

    double distance(double x1, double y1, double x2, double y2);

};

#endif