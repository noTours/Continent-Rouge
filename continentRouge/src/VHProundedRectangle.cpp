#include "VHProundedRectangle.h"

//constructor

//----------------------------------------------------------------	
VHProundedRectangle::VHProundedRectangle() {
    corner[0] = true;
    corner[1] = true;
    corner[2] = true;
    corner[3] = true;
}
VHProundedRectangle::VHProundedRectangle(float _x, float _y, float _w, float _h, float _r) : position(_x, _y), width(_w), height(_h), radius(_r) {
    corner[0] = true;
    corner[1] = true;
    corner[2] = true;
    corner[3] = true;
    setPoints();
}
VHProundedRectangle::VHProundedRectangle(float _x, float _y, float _w, float _h, float _r, bool _ul, bool _ur, bool _dl, bool _dr) : position(_x, _y), width(_w), height(_h), radius(_r) {
    corner[0] = _ul;
    corner[1] = _ur;
    corner[2] = _dl;
    corner[3] = _dr;
    setPoints();
}

// methods

//----------------------------------------------------------------
void VHProundedRectangle::set(bool _ul, bool _ur, bool _dl, bool _dr) {
    corner[0] = _ul;
    corner[1] = _ur;
    corner[2] = _dl;
    corner[3] = _dr;
    points.clear();
    setPoints();
}
void VHProundedRectangle::set(float _w, float _h) {
    width = _w;
    height = _h;
    points.clear();
    setPoints();
}

void VHProundedRectangle::setPosition(float _x, float _y) {
    position.set(_x, _y);
    points.clear();
    setPoints();
}

void VHProundedRectangle::setPoints() {
    if (corner[0]) {
        for (int i=0; i<8; i++) {
            addPoint(radius * sin(TWO_PI*(24-i)/32) + position.x + radius, radius * cos(TWO_PI*(24-i)/32) + position.y + radius);
        }
    } else {
        addPoint(position.x, position.y);
    }
    //addPoint(position.x + radius, position.y);
    //addPoint(position.x + width - radius, position.y);
    if (corner[1]) {
        for (int i=0; i<8; i++) {
            addPoint(radius * sin(TWO_PI*(16-i)/32) + position.x + width - radius, radius * cos(TWO_PI*(16-i)/32) + position.y + radius);
        }
    } else {
        addPoint(position.x + width, position.y);
    }
    //addPoint(position.x + width, position.y + radius);
    //addPoint(position.x + width, position.y + height - radius);
    if (corner[2]) {
        for (int i=0; i<8; i++) {
            addPoint(radius * sin(TWO_PI*(8-i)/32) + position.x + width - radius, radius * cos(TWO_PI*(8-i)/32) + position.y + height - radius);
        }
    } else {
        addPoint(position.x + width, position.y + height);
    }
    //addPoint(position.x + width - radius, position.y + height);
    //addPoint(position.x + radius, position.y + height);
    if (corner[3]) {
        for (int i=0; i<8; i++) {
            addPoint(radius * sin(TWO_PI*(32-i)/32) + position.x + radius, radius * cos(TWO_PI*(32-i)/32) + position.y + height - radius);
        }
    } else {
        addPoint(position.x, position.y + height);
    }
    //addPoint(position.x, position.y + height - radius);
    //addPoint(position.x, position.y + radius);
}

//----------------------------------------------------------------	

void VHProundedRectangle::draw() {
    ofBeginShape();
    for (int i=0; i<points.size(); i++) {
        ofVertex(points[i].x, points[i].y);
    }
    ofEndShape(true);
}

//--------------------------------------------------------------

void VHProundedRectangle::addPoint(const ofVec2f& _p) {
	points.push_back(ofVec2f(_p.x, _p.y));
    //ofLog(OF_LOG_VERBOSE, "addPoint %i;", points.size());
}

void VHProundedRectangle::addPoint(const float _x, const float _y) {
	points.push_back(ofVec2f(_x, _y));
    //ofLog(OF_LOG_VERBOSE, "addPoint %i;", points.size());
}

void VHProundedRectangle::removePoint(const int _n) {
    points.erase(points.begin() + _n);
}

void VHProundedRectangle::clear() {
    points.clear();
}
