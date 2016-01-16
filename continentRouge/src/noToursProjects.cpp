#include "noToursProjects.h"

//constructor

//----------------------------------------------------------------	
noToursProjects::noToursProjects() {
    loadRSS = new ofxHttpUtils;
    loadWalkers = new ofxHttpUtils;
    ofAddListener(loadRSS->newResponseEvent, this, &noToursProjects::readRSS);
    ofAddListener(loadWalkers->newResponseEvent, this, &noToursProjects::readJson);
    OSC = new VHPsendOSC;
    activeLocation = 0;
    locationsloaded = false;
}

// methods

//----------------------------------------------------------------

void noToursProjects::addProject(int _id, int _zoom, double _lat1, double _long1, double _lat2, double _long2, string _shape, ofTrueTypeFont * _TTF) {
    // Create Location
    cout << "Project " << _id << " - nw: (" << _lat1  << ", " << _long1 << "), se: (" << _lat2 << ", " << _long2 << "), svg: " << _shape << endl;
    locations.push_back(noToursLocation(_id, _zoom, _lat1, _long1, _lat2, _long2, _shape, _TTF, loadWalkers, OSC));
    // Add RSS URL
    cout << "loadRSS: http://www.editor.notours.org/projects/"+ ofToString(_id) +"/soundscape.rss" << endl;
    loadRSS->addUrl("http://www.editor.notours.org/projects/"+ ofToString(_id) +"/soundscape.rss");
}

//----------------------------------------------------------------

void noToursProjects::addButton(float _x, float _y, bool _a, string _text, float _ofsetx, float _ofsety, ofTrueTypeFont * _TTF) {
    // Create Button
    buttons.push_back(VHProundedButton(_x, _y, _a, _text, _ofsetx, _ofsety, _TTF));
    cout << "Button - position: (" << _x  << ", " << _y << "), value: " << _a << ", name: " << _text << ", ofset: (" << _ofsetx  << ", " << _ofsety << ")" << endl;
}

//----------------------------------------------------------------

void noToursProjects::loadProjects() {
    loadRSS->start();
}

//----------------------------------------------------------------

void noToursProjects::setOSC(bool _s, string _host, int _port) {
    OSC->init(_host, _port);
    if (_s) OSC->start();
}

//----------------------------------------------------------------

void noToursProjects::readRSS(ofxHttpResponse& _response) {
    ofxXmlSettings RSS;
    RSS.loadFromBuffer(_response.responseBody);      // parse string
    RSS.pushTag("rss");                             // change relative root to <rss>
    RSS.pushTag("channel");                         // change relative root to <channel>
    string link = RSS.getValue("link", "");
    vector<string> parts = ofSplitString(link, "/");
    int id = ofToInt(parts[parts.size()-2]);
    int screenWidth = ofGetScreenHeight();
    int screenHeight = ofGetScreenWidth();
    int num;
    bool loaded = true;
    for (int i=0; i<locations.size(); i++) {
        cout << " " << endl;
        cout << "RSS loaded!" << endl;
        if (locations[i].project_id==id) locations[i].loadRSS(RSS);
        if (locations[i].loaded==false) loaded = false;
    }
    if (loaded) {
        cout << "All locations loaded!" << endl;
        locationsloaded = true;
        buttons[activeLocation].set(true);
        startGetWalkers();
    }
}

//----------------------------------------------------------------

void noToursProjects::readJson(ofxHttpResponse& _response) {
    // cout << _response.status << " - " << _response.responseBody << endl;
    ofxJSONElement json;
    if (json.parse(_response.responseBody)) {
        bool error = json["error"].asBool();
        if (error) {
            if (json["error_type"].asString()=="3") {
                string msg = json["msg"].asString();
                cout << msg << endl;
            } else {
                string msg = json["error_msg"].asString();
                cout << msg << endl;
            }
        } else {
            /* ACTIONS HERE */
            string format = json["format"].asString();
            int project_id = ofToInt(json["id"].asString());
            string title = json["title"].asString();
            VHPpoint center = VHPpoint(json["x"].asDouble(), json["y"].asDouble(), json["latitude"].asString(), json["longitude"].asString());
            int zoom = ofToInt(json["zoom"].asString());
            int levels = ofToInt(json["levels"].asString());
            if (json["data"].isString()) {
                cout << " " << endl;
                cout << "Project " << json["id"].asString() << ":"<< " Nobody walking at the moment"<< endl;
            } else {
                int n = json["data"].size();
                cout << " " << endl;
                cout << "Project " << json["id"].asString() << ":"<< " Loadded " << n << " walkers" << endl;
                if (n>0) {
                    for (int u = 0; u<locations.size(); u++) {
                        if (locations[u].project_id==project_id) {
                            if (format=="byProjectId") {
                                for (int i=0; i<n; i++) {
                                    ofxJSONElement w = json["data"][i];
                                    locations[u].addWalker(w);
                                }
                            } else if (format=="byProjectIdStored") {
                                for (int i=0; i<n; i++) {
                                    ofxJSONElement w = json["data"][i];
                                    locations[u].addStoredWalker(w);
                                }
                            }
                            cout << "created " << locations[u].walkers.size() << " walkers" << endl;
                            locations[u].checkChanges();
                            break;
                        }
                    }
                }
            }
        }
    }
}

//----------------------------------------------------------------

void noToursProjects::startGetWalkers() {
    loadWalkers->start();
    for (int i=0; i<locations.size(); i++) {
        locations[i].getWalkers.start();
    }
}

//----------------------------------------------------------------

void noToursProjects::update() {
    if (locationsloaded) locations[activeLocation].update();
}

//--------------------------------------------------------------
void noToursProjects::draw(){
    ofPushStyle();
    ofNoFill();
    ofSetColor(220, 250, 220);
    ofSetLineWidth(1.3);
    if (locationsloaded) {
        for (int i=0; i<buttons.size(); i++) {
            buttons[i].display();
        }
        locations[activeLocation].draw();
    }
    ofPopStyle();
}

//--------------------------------------------------------------

void noToursProjects::keyPressed(int key) {
    if (locationsloaded) locations[activeLocation].map.keyPressed(key);
}

//--------------------------------------------------------------

void noToursProjects::keyReleased(int key) {
    if (locationsloaded) {
        locations[activeLocation].map.keyReleased(key);
        if (key == 's' || key == 'S') OSC->toggle();
    }
    
    /*
     if (start) {
     if (key == 'f' || key == 'F') {
     ofToggleFullscreen();
     } else if (key == '0' ) {
     //activeLocation = 0;
     } else if (key == '1' ) {
     locations[activeLocation].send(1);
     //activeLocation = 1;
     } else if (key == '2' ) {
     locations[activeLocation].send(2);
     //activeLocation = 2;
     } else if (key == '3' ) {
     locations[activeLocation].send(3);
     //activeLocation = 3;
     } else if (key == '4' ) {
     locations[activeLocation].send(4);
     //activeLocation = 3;
     } else if (key == '5' ) {
     locations[activeLocation].send(5);
     //activeLocation = 3;
     }
     }
     */
}
//--------------------------------------------------------------

void noToursProjects::mouseMoved(int x, int y ) {
    // TODO: change mouse cursor if over map?
}

//--------------------------------------------------------------

void noToursProjects::mouseDragged(int _x, int _y, int _button) {
    if (locationsloaded) locations[activeLocation].map.mouseDragged(_x, _y, _button);
}

//--------------------------------------------------------------

void noToursProjects::mousePressed(int _x, int _y, int _button) {
    if (locationsloaded) locations[activeLocation].mousePressed(_x, _y, _button);
}

//--------------------------------------------------------------

void noToursProjects::mouseReleased(int _x, int _y, int _button) {
    if (locationsloaded) {
        locations[activeLocation].mouseReleased(_x, _y, _button);
        for (int i=0; i<buttons.size(); i++) {
            if (buttons[i].over(_x, _y)) {
                if (buttons[i].active) {
                    buttons[i].set(false);
                } else {
                    for (int i=0; i<buttons.size(); i++) {
                        buttons[i].set(false);
                    }
                    buttons[i].set(true);
                    activeLocation = i;
                }
                break;
            }
        }
    }
}

//--------------------------------------------------------------
void noToursProjects::windowResized(int w, int h) {
    // TODO: map.setSize(w,h)?
    if (locationsloaded) {
        locations[activeLocation].map.width = w;
        locations[activeLocation].map.height = h;
    }
}

//----------------------------------------------------------------