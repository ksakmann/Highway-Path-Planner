//
// Created by ks on 08.08.17.
//

#include "Car.h"

Car::Car() {

}

Car::~Car() {

}

void Car::update(double x_in, double y_in, double s_in, double d_in, double yaw_in, double speed_in) {

    x = x_in;
    y = y_in;
    s = s_in;
    d = d_in;
    yaw = yaw_in;
    speed = speed_in;

}


