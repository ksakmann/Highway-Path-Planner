//
// Created by ks on 08.08.17.
//

#ifndef PATH_PLANNING_CAR_H
#define PATH_PLANNING_CAR_H


class Car {
public:
    double x;
    double y;
    double s;
    double d;
    double yaw;
    double speed;

    //double xPrev,yPrev,sPrev,dPrev,yawPrev,speedPrev;

    // Previous path data given to the Planner
    //auto previous_path_x = j[1]["previous_path_x"];
    //auto previous_path_y = j[1]["previous_path_y"];
    // Previous path's end s and d values
    //double end_path_s_;
    //double end_path_d_;

    Car();
    ~Car();
    void update(double x,double y,double s,double d,double yaw,double speed);

    // Sensor Fusion Data, a list of all other cars on the same side of the road.
    //auto sensor_fusion;

};


#endif //PATH_PLANNING_CAR_H
