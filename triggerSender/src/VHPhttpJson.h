#ifndef _VHP_HTTPJSON
#define _VHP_HTTPJSON

#include "ofMain.h"
#include "ofxHttpUtils.h"
#include "ofxJSON.h"

//--------------------------------------------------------
class VHPhttpJson {
public:
    
    //constructor
    VHPhttpJson();
    
    // variables
    vector<bool>        send;
    
    string              send_url_1;
    string              send_url_2;
    
    string              user_name;
    string              user_mac;
    string              project_id;
    string              auth_key;
    string              latitude;
    string              longitude;
    
    ofxHttpUtils        httpUtils;
    bool                streaming;
    int                 timer;
    bool                get;
    string              last_data[4];
    
    // methods
    void init(string _send_url_1, string _send_url_2, string _user_name, string _user_mac, string _latitude, string _longitude, string _project_id, string _auth_key);
    void update(string _user_name, string _data_name);
    void sendData(int _i);
    void newResponse(ofxHttpResponse & response);
    void start();
    void stop();
    
private:
	
};
//--------------------------------------------------------

#endif