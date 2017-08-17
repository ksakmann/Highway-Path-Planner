//
// Created by ks on 12.08.17.
//

#include <cmath>
#include "Path.h"

Path::Path() {

}

Path::Path(vector<double> x_, vector<double> y_) : x(x_),y(y_) {

}

void Path::compute_cost() {

    double speed_cost = evaluate_distance();
    cost = speed_cost;

}

double Path::evaluate_distance() {
    double distance = 0;
    for (int i = 1 ; i < x.size() ; i++ ){
        double dx = x[i]-x[i-1];
        double dy = y[i]-y[i-1];
        distance += sqrt(dx*dx + dy*dy);
    }

    return distance;
}


