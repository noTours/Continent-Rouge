#include "VHPshape.h"

//constructor

//----------------------------------------------------------------	
VHPshape::VHPshape() {
}

// methods

//----------------------------------------------------------------	
void VHPshape::loadShape(string _s) {
    //svg.load(_s);
    if( XMLShape.loadFile(_s) ){
		cout << "XMLShape loaded!" << endl;
        XMLShape.pushTag("svg"); // change relative root to <svg>
        int numPolygon = XMLShape.getNumTags("polygon");
        cout << "numPolygon: " << numPolygon << endl;
        for(int i=0; i<numPolygon; i++) {
            //XMLShape.pushTag("polygon", i); // change relative root to <polygon>
            polygons.push_back(VHPpolyline());
            int n = polygons.size() - 1;
            polygons[n].addPoints(XMLShape.getAttribute("polygon", "points", "", i));
        }
	}
    /*
    ofPath baseRect = svg.getPathAt(0);
    vector<ofPolyline> lines = baseRect.getOutline();
    cout << "baseRect size" << lines.size() << endl;
     */
}

void VHPshape::setLocation(double _lat1, double _long1, double _lat2, double _long2) {
    refLocation1 = Location(_lat1, _long1);
    refLocation3 = Location(_lat2, _long2);
}

void VHPshape::updatePosition(Map& _map) {
    refPoint1 = _map.locationPoint(refLocation1);
    refPoint3 = _map.locationPoint(refLocation3);
    if ((polygons.size()>=1)&&(polygons[0].points.size()==4)) {
        VHPpoint point1 = polygons[0].points[0];
        VHPpoint point3 = polygons[0].points[2];
        rate.set((refPoint3.x - refPoint1.x)/(point3.x - point1.x), (refPoint3.y - refPoint1.y)/(point3.y - point1.y));
        /*
        for(int i=0; i<polygons.size(); i++) {
            for(int u=0; u<polygons[i].points.size(); u++) {
                float difX = rate.x * (polygons[i].points[u].x - point1.x);
                float difY = rate.y * (polygons[i].points[u].y - point1.y);
                polygons[i].points[u].x  = refPoint1.x + difX;
                polygons[i].points[u].y  = refPoint1.y + difY;
            }
        }
         */
    }
}

void VHPshape::draw() {
    float difX;
    float difY;
    if ((polygons.size()>=1)&&(polygons[0].points.size()==4)) {
        for(int i=1; i<polygons.size(); i++) {
            ofBeginShape();
            for(int u=0; u<polygons[i].points.size(); u++) {
                difX = rate.x * (polygons[i].points[u].x - polygons[0].points[0].x);
                difY = rate.y * (polygons[i].points[u].y - polygons[0].points[0].y);
                ofVertex(refPoint1.x + difX, refPoint1.y + difY);
                //cout << "ofVertex(" << (refPoint1.x  + difX) << ", " << (refPoint1.y + difY) << ");" << endl;
            }
            difX = rate.x * (polygons[i].points[0].x - polygons[0].points[0].x);
            difY = rate.y * (polygons[i].points[0].y - polygons[0].points[0].y);
            ofVertex(refPoint1.x + difX, refPoint1.y + difY);
            ofEndShape();
        }
    }
}

//----------------------------------------------------------------
double VHPshape::string_to_double(const std::string& _s) {
    std::istringstream i(_s);
    double x;
    if (!(i >> x))
        return 0;
    return x;
}

//----------------------------------------------------------------	