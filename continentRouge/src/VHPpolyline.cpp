#include "VHPpolyline.h"

//constructor

//----------------------------------------------------------------
VHPpolyline::VHPpolyline() { }

// methods

//--------------------------------------------------------------

void VHPpolyline::addPoint(const VHPpoint& _p) {
	points.push_back(VHPpoint(_p));
}

void VHPpolyline::addPoint(const float _x, const float _y, const string _lat, const string _lon) {
	points.push_back(VHPpoint(_x, _y, _lat, _lon));
}

void VHPpolyline::removePoint(const int _n) {
    points.erase(points.begin() + _n);
}

void VHPpolyline::addPoints(const string _points) {
    vector<string> points = ofSplitString(_points, " ");
    for(int i=0; i<points.size(); i++) {
        vector<string> p = ofSplitString(points[i], ",");
        if (p.size()==2) {
            //cout << "point: " << p[0] << ", " << p[1] << endl;
            addPoint(ofToFloat(p[0]), ofToFloat(p[1]), "0", "0");
        }
    }
}