#ifndef VHP_SHAPE
#define VHP_SHAPE

#include "ofMain.h"
#include "Map.h"
#include "ofxSVG.h"
#include "ofxXmlSettings.h"
#include "VHPpoint.h"
#include "VHPpolyline.h"

//--------------------------------------------------------
class VHPshape {
    public:
    
        //constructor
        VHPshape();
        
        // variables
        Location refLocation1, refLocation3;
        Point2d refPoint1, refPoint3;
        ofVec2f rate;
        ofxSVG svg;
        ofxXmlSettings XMLShape;
        vector<VHPpolyline> polygons;
    
        // methods
        void loadShape(string _s);
        void setLocation(double _lat1, double _long1, double _lat2, double _long2);
        void updatePosition(Map& _map);
        double string_to_double(const std::string& _s);
        void draw();
    
    private:
	
};
//--------------------------------------------------------

#endif 