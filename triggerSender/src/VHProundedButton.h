#ifndef _VHP_RBUTTON
#define _VHP_RBUTTON

#include "ofMain.h"
#include "VHPbutton.h"
#include "VHProundedRectangle.h"

#define RBUTTON_OVER_MARGIN         8
#define DEFAULT_RBUTTON_WIDTH       30
#define DEFAULT_RBUTTON_HEIGHT      30
#define DEFAULT_RBUTTON_CORNER      8

//--------------------------------------------------------
class VHProundedButton : public VHPbutton {
    public:
    
        //constructor
        VHProundedButton();
        VHProundedButton(float _x, float _y, ofTrueTypeFont * _TTF);
        VHProundedButton(float _x, float _y, int _w, int _h, ofTrueTypeFont * _TTF);
        VHProundedButton(float _x, float _y, bool _a, string _text, float _ofsetx, float _ofsety, ofTrueTypeFont * _TTF);
    
        // variables
        float ofsetx;
        float ofsety;
        VHProundedRectangle shape;
        ofTrueTypeFont * font;
        string text;
    
        // methods
        void init(float _x, float _y, bool _a, string _text, float _ofsetx, float _ofsety, ofTrueTypeFont * _TTF);
        void setPosition(float _x, float _y);
        void setText(string _text, float _ofsetx, float _ofsety) ;
        void display();
        void display(float _a);
        bool over(const float& _x, const float& _y);
        bool over(const ofVec2f& _p);
    
    private:
	
};
//--------------------------------------------------------

#endif 