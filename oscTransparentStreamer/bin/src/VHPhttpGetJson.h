#ifndef _VHP_HTTPGETJSON
#define _VHP_HTTPGETJSON

#include "ofMain.h"
#include "ofxHttpUtils.h"
#include "ofxOsc.h"
#include "ofxJSON.h"
#include "noToursWalker.h"

//--------------------------------------------------------
class VHPhttpGetJson {
public:
    
    //constructor
    VHPhttpGetJson();
    
    // variables
    
    string                  get_url;
    
    string                  project_id;
    string                  last;
    string                  auth_key;
    vector<noToursWalker>   walkers;
    bool                    hasWalkers;
    
    ofxHttpUtils        httpUtils;
    ofxOscSender *      sender;
    bool                streaming;
    int                 timer;
    int                 reset;
    
    // methods
    void init(string _get_url, string _last, string _project_id, string _auth_key, string _host, int _port, int _reset);
    void update();
    void getData();
    void newResponse(ofxHttpResponse & _response);
    void updateWalkers(string _data);
    void addWalker(ofxJSONElement& _w);
    void checkArrival(vector<noToursWalker> & _walkers);
    void send(int _i);
    void start();
    void stop();
    
    
private:
	
};
//--------------------------------------------------------

#endif