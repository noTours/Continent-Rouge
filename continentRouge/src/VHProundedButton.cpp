#include "VHProundedButton.h"

//constructor

//----------------------------------------------------------------	
VHProundedButton::VHProundedButton() : VHPbutton() {
    shape = VHProundedRectangle(0.0, 0.0, DEFAULT_RBUTTON_WIDTH, DEFAULT_RBUTTON_HEIGHT, DEFAULT_RBUTTON_CORNER);
}
VHProundedButton::VHProundedButton(float _x, float _y, ofTrueTypeFont * _TTF) : VHPbutton() {
    shape = VHProundedRectangle(_x, _y, DEFAULT_RBUTTON_WIDTH, DEFAULT_RBUTTON_HEIGHT, DEFAULT_RBUTTON_CORNER);
    font = _TTF;
}
VHProundedButton::VHProundedButton(float _x, float _y, int _w, int _h, ofTrueTypeFont * _TTF) : VHPbutton() {
    shape = VHProundedRectangle(_x, _y, _w, _h, DEFAULT_RBUTTON_CORNER);
    font = _TTF;
}
VHProundedButton::VHProundedButton(float _x, float _y, bool _a, string _text, float _ofsetx, float _ofsety, ofTrueTypeFont * _TTF) : VHPbutton() {
    shape = VHProundedRectangle(0.0, 0.0, DEFAULT_RBUTTON_WIDTH, DEFAULT_RBUTTON_HEIGHT, DEFAULT_RBUTTON_CORNER);
    setPosition(_x, _y);
    setText(_text, _ofsetx, _ofsety);
    font = _TTF;
    set(_a);
}
// methods

//----------------------------------------------------------------	

void VHProundedButton::init(float _x, float _y, bool _a, string _text, float _ofsetx, float _ofsety, ofTrueTypeFont * _TTF) {
    shape = VHProundedRectangle(0.0, 0.0, DEFAULT_RBUTTON_WIDTH, DEFAULT_RBUTTON_HEIGHT, DEFAULT_RBUTTON_CORNER);
    setPosition(_x, _y);
    setText(_text, _ofsetx, _ofsety);
    font = _TTF;
    set(_a);
}

void VHProundedButton::setPosition(float _x, float _y) {
    shape.setPosition(_x, _y);
}

void VHProundedButton::setText(string _text, float _ofsetx, float _ofsety) {
    ofsetx = _ofsetx;
    ofsety = _ofsety;
    text = _text;
}

//----------------------------------------------------------------

void VHProundedButton::display() {
    ofPushStyle();
        active ? ofFill() : ofNoFill();
        ofSetColor(activeFillColor);
        shape.draw();
        ofNoFill();
        ofSetColor(activeLineColor);
        shape.draw();
        if (text!="") {
            ofSetColor(activeLineColor);
            font->drawString(text, shape.points[0].x + ofsetx, shape.points[0].y + ofsety);
        }
    ofPopStyle();
    
    /*
    ofFill();
    ofSetColor(fillColor);
    if (active) {
        ofSetColor(activeFillColor);
    } else {
        ofSetColor(fillColor);
    }
    ofFill();
    shape.draw();
    ofNoFill();
    ofSetLineWidth(0.4);
    if (active) {
        ofSetColor(activeLineColor);
    } else {
        ofSetColor(lineColor);
    }
    shape.draw();
    */
}
void VHProundedButton::display(float _a) {
    ofFill();
    if (active) {
        ofSetColor(activeFillColor.r, activeFillColor.g, activeFillColor.b, activeFillColor.a* _a);
    } else {
        ofSetColor(fillColor.r, fillColor.g, fillColor.b, fillColor.a* _a);
    }
    shape.draw();
    ofNoFill();
    ofSetLineWidth(0.4);
    if (active) {
        ofSetColor(activeLineColor.r, activeLineColor.g, activeLineColor.b, activeLineColor.a* _a);
    } else {
        ofSetColor(lineColor.r, lineColor.g, lineColor.b, lineColor.a* _a);
    }
    shape.draw();
}

//----------------------------------------------------------------	

bool VHProundedButton::over(const float& _x, const float& _y) {
    if ((_x>=shape.position.x - OVER_MARGIN)&&(_x<=shape.position.x + shape.width + OVER_MARGIN)&&(_y>=shape.position.y - OVER_MARGIN)&&(_y<=shape.position.y + shape.width + OVER_MARGIN)) {
        return true;
    } else {
        return false;
    }  
}

bool VHProundedButton::over(const ofVec2f& _p) {
    return over(_p.x, _p.y);
}


//----------------------------------------------------------------	
