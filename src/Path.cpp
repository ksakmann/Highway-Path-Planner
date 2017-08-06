#include <math.h>
#include "Path.h"
using namespace std;

Path::Path(vector<double> X_in,vector<double> Y_in, double distInc) : X_(X_in), Y_(Y_in) {
		Path::get_pathDistance();
		Path::fit_splines();
		Path::get_interpolatedPath(distInc);
}

Path::~Path(){};

void Path::get_pathDistance() {

		pathDistance.push_back(0.0);
		assert(X_.size() == Y_.size());
		for (auto i = 0 ; i < X_.size() - 1 ; ++i){
			pathDistance.push_back(pathDistance[i]+distance(X_[i],Y_[i],X_[i+1],Y_[i+1]));
		}
		pathLength = pathDistance[X_.size()-1];
}

void Path::fit_splines() {

		sx.set_points(pathDistance,X_);    
		sy.set_points(pathDistance,Y_);    

}

void Path::get_interpolatedPath(double distInc){

		double distance = 0;
		while (distance < pathLength){
			X.push_back(sx(distance));
			Y.push_back(sy(distance));
			distance += distInc;
		}

}

double Path::distance(double x1, double y1, double x2, double y2){
		return sqrt((x2-x1)*(x2-x1)+(y2-y1)*(y2-y1));
}
