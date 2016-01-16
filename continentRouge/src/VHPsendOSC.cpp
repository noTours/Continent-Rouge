#include "VHPsendOSC.h"

//constructor

//----------------------------------------------------------------
VHPsendOSC::VHPsendOSC() {
}

// methods

//--------------------------------------------------------------

void VHPsendOSC::init(string _host, int _port) {
    
    streaming = false;
    
    // open an outgoing connection to HOST:PORT
    sender = new ofxOscSender;
    sender->setup(_host, _port);
    cout << "OSC HOST: " << _host << " PORT: " << _port << endl;
  
}

//--------------------------------------------------------------

void VHPsendOSC::addMsg(ofxOscMessage _msg) {
    if (streaming) {
        sender->sendMessage(_msg);
    }
}


//--------------------------------------------------------------

void VHPsendOSC::addStringMsg(string _addres, string _msg) {
    if (streaming) {
        ofxOscMessage m;
        m.setAddress(_addres);
        m.addStringArg(_msg);
        sender->sendMessage(m);
    }
}

//----------------------------------------------------------------

void VHPsendOSC::toggle() {
    streaming ? stop() : start();
}

void toggle();
//----------------------------------------------------------------

void VHPsendOSC::start() {
    streaming = true;
    // send OSC start message
    cout << "start OSC" << endl;
    addStringMsg("/tech", "start");
}

//----------------------------------------------------------------

void VHPsendOSC::stop() {
    // send OSC stop message
    cout << "stop OSC" << endl;
    addStringMsg("/tech", "stop");
    streaming = false;
}

//----------------------------------------------------------------