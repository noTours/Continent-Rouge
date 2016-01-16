#ifndef _VHP_FONT
#define _VHP_FONT
#include "ofMain.h"
#include "VHPpoint.h"
#include "VHPtrueTypeFont.h"

//--------------------------------------------------------
class VHPtrueTypeFont : public ofTrueTypeFont {
    
    public:
    
        //constructor
        VHPtrueTypeFont();
    
        // variables
        float paragraph_w;
    
        // methods
        void setParagraphWidth(float _w);
    
        void drawSpecialString(string c, float x, float y);
        void drawAllCharecters(float x, float y);
        float stringWidth(string c);
        ofRectangle getStringBoundingBox(string c, float x, float y);
    
    private:
	
};
//--------------------------------------------------------

#endif 