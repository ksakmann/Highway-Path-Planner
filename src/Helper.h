//
// Created by ks on 13.08.17.
//

#ifndef PATH_PLANNING_HELPER_H
#define PATH_PLANNING_HELPER_H

#include <math.h>
#include <vector>
#include <string>

using namespace std;

// For converting back and forth between radians and degrees.
constexpr double pi();

double deg2rad(double x);

double rad2deg(double x);

double distance(double x1, double y1, double x2, double y2);

// Checks if the SocketIO event has JSON data.
// If there is data the JSON object in string format will be returned,
// else the empty string "" will be returned.
string hasData(string s);

int ClosestWaypoint(double x, double y, vector<double> maps_x, vector<double> maps_y);

int NextWaypoint(double x, double y, double theta, vector<double> maps_x, vector<double> maps_y) ;
// Transform from Cartesian x,y coordinates to Frenet s,d coordinates
vector<double> getFrenet(double x, double y, double theta, vector<double> maps_x, vector<double> maps_y);
// Transform from Frenet s,d coordinates to Cartesian x,y
vector<double> getXY(double s, double d, vector<double> maps_s, vector<double> maps_x, vector<double> maps_y);


#endif //PATH_PLANNING_HELPER_H
