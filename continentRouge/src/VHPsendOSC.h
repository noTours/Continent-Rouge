#ifndef _VHP_SENDOSC
#define _VHP_SENDOSC

#include "ofMain.h"
#include "ofxOsc.h"

//--------------------------------------------------------
class VHPsendOSC {
    public:
    
        //constructor
        VHPsendOSC();
    
        // variables
        ofxOscSender *      sender;
        bool                streaming;
    
        // methods
        void init(string _host, int _port);
        void addMsg(ofxOscMessage _msg);
        void addStringMsg(string _addres, string _msg);
        void toggle();
        void start();
        void stop();
    
    
    private:
	
};
//--------------------------------------------------------

#endif