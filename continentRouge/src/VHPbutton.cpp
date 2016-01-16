#include "VHPbutton.h"

//constructor

//----------------------------------------------------------------	
VHPbutton::VHPbutton() {
    active = false;
    lineColor.set(255, 255, 120, 190);
    activeLineColor.set(255, 255, 120, 190);
    fillColor.set(0, 255, 128, 0);
    activeFillColor.set (0, 255, 128, 120);
}

// methods

//----------------------------------------------------------------	

void VHPbutton::set(bool _a) {
    active = _a;
}
void VHPbutton::toggle() {
    active = !active;
}

//----------------------------------------------------------------	