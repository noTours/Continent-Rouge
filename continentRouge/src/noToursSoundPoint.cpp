#include "noToursSoundPoint.h"

//constructor

//----------------------------------------------------------------	
noToursSoundPoint::noToursSoundPoint() : playing(false), moving(false), milestone(0), arrival(0), grow_r(50.0), grow_d(6.0){ }
noToursSoundPoint::noToursSoundPoint(string _lat, string _long, string _x, string _y, string _r, string _l) {
    title = "";
    description = "";
    soundPath = "";
    location = Location(string_to_double(_lat), string_to_double(_long));
    radius =  ofToFloat(_r);
    radiusLocation = Location(location.lat, getLongAtDistance(location.lat, location.lon, radius));
    position = Point2d( ofToFloat(_x),  ofToFloat(_y));
    level = ofToInt(_l);
    milestone = 0;
    arrival = 0;
    playing = false;
    moving = false;
    grow_r = 50.0;
    grow_d = 6.0;
}
noToursSoundPoint::noToursSoundPoint(string _title, string _description, string _l, string _lat, string _long, string _r, vector<string> _a) {
    title = _title;
    description = _description;
    soundPath = "";
    location = Location(string_to_double(_lat), string_to_double(_long));
    radius =  ofToFloat(_r);
    radiusLocation = Location(location.lat, getLongAtDistance(location.lat, location.lon, radius));
    level = ofToInt(_l);
    milestone = 0;
    arrival = 0;
    attributes = _a;
    playing = false;
    moving = false;
    grow_r = 50.0;
    grow_d = 6.0;
}


// methods

//----------------------------------------------------------------	
void noToursSoundPoint::setTitle(string _title) {
    title = _title;
    // cout << title << endl;
}

void noToursSoundPoint::setDescription(string _description) {
    description = _description;
    // cout << description << endl;
}

void noToursSoundPoint::setSoundPath(string _path) {
    vector<string> path = ofSplitString(_path, "/");
    if (path.size()>=3) soundPath = path[2];
    sound.loadSound("sound/"+soundPath);
    sound.setLoop(true);
    volume = 0.0;
    sound.setVolume(volume);
    // sound.setMultiPlay(true);
    // cout << soundPath << endl;
}

void noToursSoundPoint::setAttributes(vector<string> _a) {
    attributes = _a;
    // cout << attributes.size() << " attributes:" << endl;
    for(int u=0; u<attributes.size(); u++) {
        // cout << attributes[u] << endl;
    }
}

void noToursSoundPoint::setLevel(int _l) {
    level = _l;
    // cout << level << endl;
}

void noToursSoundPoint::setMilestone(int _m) {
    milestone = _m;
    // cout << milestone << endl;
}

void noToursSoundPoint::setArrival(int _a) {
    arrival = _a;
    // cout << arrival << endl;
}

void noToursSoundPoint::parseGeorssData(vector<string> _georssData) {
    if (_georssData.size()==3) {
        location = Location(string_to_double(_georssData[0]), string_to_double(_georssData[1]));
        radius = ofToFloat(_georssData[2]);
        radiusLocation = Location(location.lat, getLongAtDistance(location.lat, location.lon, radius));
        // cout << "location: " << location.lat << ", " << location.lon << endl;
        // cout << "radius: " << radius << "." << endl;
        // cout << "radiusLocation: " << radiusLocation.lat << ", " << radiusLocation.lon << endl;
    }
}

//----------------------------------------------------------------
void noToursSoundPoint::updatePosition(Map& _map) {
    position = _map.locationPoint(location);
    radiusPosition = _map.locationPoint(radiusLocation);
    screenRadius = abs((position.x - radiusPosition.x));
    // cout << "position: " << position.x << ", " << position.y << endl;
    // cout << "radiusPosition: " << radiusPosition.x << ", " << radiusPosition.y << endl;
    // cout << " " << endl;
}

double noToursSoundPoint::getLongAtDistance(double _lat, double _long, float _dist) {
    double R = 6371000;
    double lat = _lat * DEG_TO_RAD;
    double lng = _long * DEG_TO_RAD;
    return (lng + (acos((cos(_dist/R)-sin(lat)*sin(lat))/(cos(lat)*cos(lat))))) * RAD_TO_DEG;
}

double noToursSoundPoint::string_to_double(const std::string& _s) {
    std::istringstream i(_s);
    double x;
    if (!(i >> x))
        return 0;
    return x;
}

//----------------------------------------------------------------
void noToursSoundPoint::drawSimple() {
    ofPushStyle();
    ofSetColor(0, 255, 128, 40);
    if (milestone!=0) {
        ofSetColor(255, 12, 6, 120);
    }
    if (arrival!=0) {
        ofSetColor(12, 6, 255, 120);
    }
    ofFill();
    ofCircle(position.x, position.y, screenRadius);
    ofSetColor(255, 255, 0, 90);
    if (milestone!=0) {
        ofSetColor(255, 12, 60, 190);
    }
    if (arrival!=0) {
        ofSetColor(12, 60, 255, 190);
    }
    ofNoFill();
    ofCircle(position.x, position.y, screenRadius);
    ofPopStyle();
}

void noToursSoundPoint::draw() {
    
    ofPushStyle();
    ofEnableSmoothing();
    ofSetLineWidth(1.3);
    ofSetCircleResolution(120);
    
    if (moving) {
        
        int t = (int)(grow_r * grow_d + ofGetFrameNum() - playerStart) % (int)(grow_r * 2 * grow_d);
        if ((playing)&&((ofGetFrameNum() - playerStart)>=grow_r * grow_d * 6)&&(t= grow_r * grow_d)) {
            moving = false;
        } if ((!playing)&&(t==grow_r * grow_d)) {
            moving = false;
        }
        // cout << "grow: " << grow(screenRadius/10, t, 50.0) << endl;
        // cout << "timer: " << tm << endl;
        // cout << "screenRadius/10: " << screenRadius/10 << endl;

        float r = screenRadius + grow(screenRadius/10, t, grow_r);
        ofSetColor(0, 255, 128, 10 + grow(60, t, grow_r));
        ofFill();
        ofCircle(position.x, position.y, r);
        ofSetColor(255, 255, 0, 100);
        ofNoFill();
        ofCircle(position.x, position.y, r);
        
        r = screenRadius + grow(screenRadius/7, t, grow_r);
        ofSetColor(0, 255, 128, 20 + grow(60, t, grow_r));
        ofFill();
        ofCircle(position.x, position.y, r);
        ofSetColor(255, 255, 0, 190);
        ofNoFill();
        ofCircle(position.x, position.y, r);
        
        r = screenRadius + grow(screenRadius/4, t, grow_r);
        ofSetColor(0, 255, 128, 40 + grow(60, t, grow_r));
        ofFill();
        ofCircle(position.x, position.y, r);
        ofSetColor(255, 255, 0, 255);
        ofNoFill();
        ofCircle(position.x, position.y, r);
        
        /*
        if (milestone!=0) {
            if (tm>=600) {
                moving = false;
                tm = 0;
            }
            float r = screenRadius - screenRadius/10 + grow(screenRadius/10, tm, 50.0);
            
             // cout << "grow: " << grow(screenRadius/10, tm, 50.0) << endl;
             // cout << "timer: " << tm << endl;
             // cout << "screenRadius/10: " << screenRadius/10 << endl;
             
            ofSetColor(255, 12, 6, 160 + grow(40, tm, 50.0));
            ofFill();
            ofCircle(position.x, position.y, r);
            ofSetColor(255, 12, 60, 255);
            ofNoFill();
            ofCircle(position.x, position.y, r);
            r = screenRadius - screenRadius/12 + grow(screenRadius/7, tm, 50.0);
            ofSetColor(255, 12, 6, 140 + grow(40, tm, 50.0));
            ofFill();
            ofCircle(position.x, position.y, r);
            ofSetColor(255, 255, 0, 190);
            ofSetColor(255, 12, 60, 190);
            ofNoFill();
            ofCircle(position.x, position.y, r);
            r = screenRadius - screenRadius/14 + grow(screenRadius/4, tm, 50.0);
            ofSetColor(255, 12, 6, 120 + grow(40, tm, 50.0));
            ofFill();
            ofCircle(position.x, position.y, r);
            ofSetColor(255, 12, 60, 100);
            ofNoFill();
            ofCircle(position.x, position.y, r);
            tm++;

        } else {
            // Normal circle appearance (no movement)
            ofSetColor(0, 255, 128, 40);
            if (milestone!=0) {
                ofSetColor(255, 12, 6, 120);
            }
            if (arrival!=0) {
                ofSetColor(12, 6, 255, 120);
            }
            ofFill();
            ofCircle(position.x, position.y, screenRadius);
            ofSetColor(255, 255, 0, 90);
            if (milestone!=0) {
                ofSetColor(255, 12, 60, 190);
            }
            if (arrival!=0) {
                ofSetColor(12, 60, 255, 190);
            }
            ofNoFill();
            ofCircle(position.x, position.y, screenRadius);
            
            
        //}*/
        
    } else {
        drawSimple();
    }
    ofPopStyle();
}

//----------------------------------------------------------------
float noToursSoundPoint::grow(float _a, const float& _p, float _r) {
    return abs(_r - _p/grow_d) * (_a / _r);
}

//----------------------------------------------------------------
ofxOscMessage noToursSoundPoint::stop() {
    playing = false;
    stopping = true;
    return mgs(soundPath, 0);
}
ofxOscMessage noToursSoundPoint::play() {
    playing = true;
    moving = true;
    stopping = false;
    playerStart = ofGetFrameNum();
    sound.play();
    cout << "sound.play();" << endl;
    return mgs(soundPath, 1);
}

ofxOscMessage noToursSoundPoint::mgs(string _audio, int _playing) {
    vector<string> ext = ofSplitString(_audio, ".");
    ofxOscMessage m;
    if (ext.size()==2) {
        if (ext[1] == "mp3") {
            m.setAddress("/path/mp3");
            m.addStringArg(_audio);
            m.addIntArg(_playing);
        } else {
            m.setAddress("/path/wav");
            m.addStringArg(_audio);
            m.addIntArg(_playing);
        }
    }
    return m;
}

bool noToursSoundPoint::checkOver(float _x, float _y) {
    double d = sqrt(pow(_x - position.x, 2) + pow(_y - position.y, 2));
    // cout << "d: " << d << " screenRadius: " << screenRadius << endl;
    // if (milestone!=0) cout << "d: " << d << " screenRadius: " << screenRadius << endl;
    bool c = false;
    if (d<screenRadius) {
        //if (milestone!=0) cout << "Milestone Active: " << endl;
        c = true;
    }
    return c;
}

//----------------------------------------------------------------

void noToursSoundPoint::fadeIn(){
    volume = ofLerp(volume, 1, 0.005); // fade slowly to 1
    sound.setVolume(volume);
}

//----------------------------------------------------------------

void noToursSoundPoint::fadeOut(){
    volume = ofLerp(volume, 0, 0.005); // fade slowly to 0
    sound.setVolume(volume);
}

//----------------------------------------------------------------

void noToursSoundPoint::updateSound() {
    if ((playing)&&(volume<1)) {
        fadeIn();
    } else if ((stopping)&&(volume>=0.01)) {
        fadeOut();
    } else if ((stopping)&&(volume<0.01)) {
        cout << "sound.stop();" << endl;
        volume = 0;
        sound.setVolume(volume);
        sound.stop();
        stopping = false;
    }
}

//----------------------------------------------------------------