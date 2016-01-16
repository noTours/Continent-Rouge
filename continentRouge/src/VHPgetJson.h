#ifndef _VHP_GETJSON
#define _VHP_GETJSON

#include "ofMain.h"
#include "ofxJSON.h"
#include "ofxOsc.h"
#include "ofxHttpUtils.h"

//--------------------------------------------------------
class VHPgetJson {
    public:
    
        //constructor
        VHPgetJson();
    
        // variables
        string                      url;
        vector<string>              fields;
        vector<string>              values;
        ofxHttpUtils *              http;
        bool                        streaming;
        int                         timer;
        int                         interval;
    
        // methods
        void init();
        void addField(string _field, string _value);
        void setUrl(string _url);
        void setHttpUtils(ofxHttpUtils * _http);
        void setInterval(int _t);
        void update();
        void getData();
        void start();
        void stop();
    
private:
	
};
//--------------------------------------------------------

#endif