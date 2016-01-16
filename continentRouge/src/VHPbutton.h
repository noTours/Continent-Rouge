#ifndef _VHP_BUTTON
#define _VHP_BUTTON

#include "ofMain.h"

#define OVER_MARGIN		4
#define DEFAULT_SIZE    14

//--------------------------------------------------------
class VHPbutton {
    public:
    
        //constructor
        VHPbutton();
        
        // variables
        bool active;
        ofColor lineColor;
        ofColor fillColor;
        ofColor activeFillColor;
        ofColor activeLineColor;
    
        // methods
        void set(bool _a);
        void toggle();
        void setPosition(float _x, float _y);
    
    private:
	
};
//--------------------------------------------------------

#endif 