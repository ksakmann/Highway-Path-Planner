#include "Waypoints.h"


Waypoints::Waypoints(vector<double> x,vector<double> y,vector<double> s,
					 vector<double> d_x,vector<double> d_y) : 
					 x_(x) ,y_(y), s_(s), d_x_(d_x), d_y_(d_y) {

	 				 fit_splines();

}

// spline interpolation of all given waypoint values as a function of s 
void Waypoints::fit_splines() {

	sx.set_points(s_,x_);    
	sy.set_points(s_,y_);    
	snx.set_points(s_,d_x_);    
	sny.set_points(s_,d_y_);    

}

// get values at interpolation points
vector<double> Waypoints::get_X(double s, double d) {

	double xi = sx(s);
	double yi = sy(s);
	double nx = snx(s);
	double ny = sny(s);

	xi += nx * d;
	yi += ny * d;

	return {xi,yi};

}




