#ifndef VHP_POLYLINE
#define VHP_POLYLINE

#include "ofMain.h"
#include "VHPpoint.h"

//--------------------------------------------------------
class VHPpolyline {
    
    public:
    
        //constructor
        VHPpolyline();
    
        // variables
        vector<VHPpoint> points;
    
        // methods
        void addPoint(const VHPpoint& _p);
        void addPoint(const float _x, const float _y, const string _lat, const string _lon);
        void removePoint(const int _n);
        void addPoints(const string _points);
        
    private:
	
};
//--------------------------------------------------------

#endif 