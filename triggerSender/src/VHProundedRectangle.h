#ifndef _VHP_ROUNDEDRECTANGLE
#define _VHP_ROUNDEDRECTANGLE

#include "ofMain.h"

//--------------------------------------------------------
class VHProundedRectangle {
    public:
    
        //constructor
        VHProundedRectangle();
        VHProundedRectangle(float _x, float _y, float _w, float _h, float _r);
        VHProundedRectangle(float _x, float _y, float _w, float _h, float _r, bool _ul, bool _ur, bool _dl, bool _dr);
        
        // variables
        float radius;
        float width;    
        float height;
        ofVec2f position;
        vector<ofVec2f> points;
        bool corner[4];
    
        // methods
        void set(bool _ul, bool _ur, bool _dl, bool _dr);
        void set(float _w, float _h);
        void setPosition(float _x, float _y);
        void setPoints();
        void draw();
    
        void addPoint(const ofVec2f& _p);
        void addPoint(const float _x, const float _y) ;
        void removePoint(const int _n);
        void clear();
    
    private:
	
};
//--------------------------------------------------------

#endif 