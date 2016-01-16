#include "VHPpoint.h"

//constructor

//----------------------------------------------------------------

VHPpoint::VHPpoint() : x(0), y(0), lat(0), lon(0) { }
VHPpoint::VHPpoint(const float _x, const float _y, const std::string& _lat, const std::string& _lon) : x(_x), y(_y) {
    lat = string_to_double(_lat);
    lon = string_to_double(_lon);
}
VHPpoint::VHPpoint(const VHPpoint& _point) : x(_point.x), y(_point.y), lat(_point.lat), lon(_point.lon) { }
VHPpoint::VHPpoint(const Location& _location) : lat(_location.lat), lon(_location.lon) { }
VHPpoint::VHPpoint(const Point2d& _point) : x(_point.x), y(_point.y) { }
VHPpoint::VHPpoint(const std::string& _lat, const std::string& _lon) {
    lat = string_to_double(_lat);
    lon = string_to_double(_lon);
}

// methods

//----------------------------------------------------------------

void VHPpoint::setPosition(float _x, float _y) {
    x = _x;
    y = _y;
}
void VHPpoint::setPosition(const VHPpoint& _p) {
    x = _p.x;
    y = _p.y;
    lat = _p.lat;
    lon = _p.lon;
}

void VHPpoint::setPositionX(float _x) {
    x = _x;
}

void VHPpoint::setPositionY(float _y) {
    y = _y;
}

void VHPpoint::setLocation(std::string _lat, std::string _lon) {
    if ((_lat!="")&&(_lon!="")) {
        lat = string_to_double(_lat);
        lon = string_to_double(_lon);
    }
}

//----------------------------------------------------------------	

// ofVec2f distance;
float VHPpoint::distance(const VHPpoint& _p) const {
    float vx = x - _p.x;
    float vy = y - _p.y;
    return (float)sqrt(vx*vx + vy*vy);
}
float VHPpoint::distance(float _x, float _y) const {
    float vx = x - _x;
    float vy = y - _y;
    return (float)sqrt(vx*vx + vy*vy);
}

// ofVec2f squareDistance;
float VHPpoint::squareDistance(const VHPpoint& _p ) const {
    float vx = x - _p.x;
    float vy = y - _p.y;
    return (float) vx*vx + vy*vy;
}
float VHPpoint::squareDistance(float _x, float _y) const {
    float vx = x - _x;
    float vy = y - _y;
    return (float) vx*vx + vy*vy;
}

//----------------------------------------------------------------	

// ofVec2f * operator;
VHPpoint VHPpoint::operator*( const float _f ) const {
    //return VHPpoint(x*_f, y*_f);
}

// ofVec2f -= operator;
VHPpoint& VHPpoint::operator-=( const VHPpoint& _p ) {
	x -= _p.x;
	y -= _p.y;
	return *this;
}

//----------------------------------------------------------------
double VHPpoint::string_to_double(const std::string& _s) {
    std::istringstream i(_s);
    double x;
    if (!(i >> x))
        return 0;
    return x;
}

//----------------------------------------------------------------
void VHPpoint::updatePosition(Map &_map) {
    Point2d position = _map.locationPoint(Location(lat,lon));
    x = position.x;
    y = position.y;
    // cout << "position: " << x << ", " << y << endl;
}

//----------------------------------------------------------------