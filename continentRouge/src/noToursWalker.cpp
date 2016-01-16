#include "noToursWalker.h"

//constructor

//----------------------------------------------------------------	
noToursWalker::noToursWalker() {
}
noToursWalker::noToursWalker(int _id, int _project_id, string _lat, string _lon, string _time, ofTrueTypeFont * _TTF) {
    id = _id;
    timer = 1000;
    color.set(ofRandom(175) + 40, ofRandom(175) + 40, ofRandom(175) + 40);
    project_id = _project_id;
    triggered = false;
    trigger = false;
    level = 1;
    level_txt = "level "+ ofToString(level);
    position = VHPpoint(_lat, _lon);
    path.push_back(VHPpoint(_lat, _lon));
    time = _time;
    type = "live";
    n = 0;
    on = false;
    font = _TTF;
    //font.loadFont("verdana.ttf", 12, false, true);
}
noToursWalker::noToursWalker(int _id, int _project_id, string _data, ofTrueTypeFont * _TTF) {
    id = _id;
    timer = 1000;
    color.set(ofRandom(175) + 40, ofRandom(175) + 40, ofRandom(175) + 40);
    project_id = _project_id;
    triggered = false;
    trigger = false;
    level = 1;
    level_txt = "level "+ ofToString(level);
    addData(_data);
    type = "stored";
    n = 0;
    on = false;
    font = _TTF;
    //font.loadFont("verdana.ttf", 12, false, true);
}

// methods

//----------------------------------------------------------------
void noToursWalker::info() {
    cout << id << " / " << project_id << " / " << position.x << ", " << position.y << " / " << time << endl;
}

//----------------------------------------------------------------
void noToursWalker::draw(int _t) {
    drawPath();
    //if ((position.x!=0)&&(position.y!=0)) drawPosition();
    drawPosition();
    if (timer>0) {
        //ofNoFill();
        
        /*
        cout << "path: " << path.size() << endl;
        cout << "location: " << position.lat << ", " << position.lon << endl;
        cout << "position: " << position.x << ", " << position.y << endl;
        */
        
        
        /*
        for (int i=4; i<=path.size()-2; i++) {
            float t = ((float)i/path.size());
            //ofPath line;
            //line.setStrokeColor(ofColor(color.r * t, color.g * t, color.b * t, 200 * t + 55));
            //line.setStrokeWidth(4*t + 1);
            
            //cout << path[i-4].x << endl;*/
            /*
            line.moveTo(path[i-4].x, path[i-4].y);
            line.curveTo(path[i-3].x, path[i-3].y);
            line.curveTo(path[i-2].x, path[i-2].y);
            line.curveTo(path[i-1].x, path[i-1].y);
            line.curveTo(path[i].x, path[i].y);
            if (i==path.size()-2) {
                x = near(path[i].y, path[i+1].y, _t);
                y = near(path[i].x, path[i+1].x, _t);
                line.curveTo(x, y);
            }
             */
        //}
        
        /*
        
        */
    }
}

void noToursWalker::drawPath() {
    
    ofPushStyle();
    
    ofNoFill();
    //cout << "drawing walker " << id << " path.size() = " << path.size() << endl;
    /*
    vector<VHPpoint> cleanPath;
    for (int i=0; i<=path.size(); i++) {
        if((path[i].x>0)&&(path[i].x<=ofGetScreenWidth())&&(path[i].y>0)&&(path[i].y<=ofGetScreenHeight())){
            cleanPath.push_back(path[i]);
        }
    }
     */
    if (path.size()>8) {
        int last;
        for (int i=4; i<=path.size()-4; i++) {
            float t;
            if (type=="stored") {
                if (i>n) break;
                t = (float)i/n;
            } else {
                t = (float)i/path.size();
                //cout << "drawing walker " << id << " t = " << t << endl;
            }
            ofSetColor(ofColor(color.r * t, color.g * t, color.b * t, 200 * t + 55));
            ofSetLineWidth(4*t + 1);
            ofBeginShape();
            ofCurveVertex(path[i].x, path[i].y);
            ofCurveVertex(path[i-1].x, path[i-1].y);
            ofCurveVertex(path[i-2].x, path[i-2].y);
            ofCurveVertex(path[i-3].x, path[i-3].y);
            ofCurveVertex(path[i-4].x, path[i-4].y);
            ofEndShape();
            last = i;
        }
        ofSetColor(ofColor(color.r, color.g, color.b, 255));
        ofSetLineWidth(5);
        ofBeginShape();
        ofCurveVertex(path[0].x, path[0].y);
        ofCurveVertex(path[last].x, path[last].y);
        ofCurveVertex(position.x, position.y);
        ofEndShape();
    }
        /*
    ofSetLineWidth(2);
    ofSetColor(color);
    ofNoFill();
    ofBeginShape();
    for (int i=0; i<path.size(); i++) {
        ofCurveVertex(path[i].x, path[i].y);
        if (i>=n) break;
    }
    ofEndShape();
    */
    
    ofPopStyle();
}

void noToursWalker::drawPosition() {
    
    ofPushStyle();
    
    ofEnableSmoothing();
    ofSetLineWidth(1.3);
    ofSetCircleResolution(64);
    
    ofSetColor(color, 255);
    //font->drawString("("+ ofToString((float)position.lat) +", "+ ofToString((float)position.lon) +") "+ milestone, position.x + 16, position.y + 16);
    font->drawString(level_txt, position.x + 16, position.y + 3);
    
    ofFill();
    ofSetColor(255, 255, 255, 120);
    ofCircle(position.x, position.y, 8);
    ofNoFill();
    ofSetColor(color, 120);
    ofCircle(position.x, position.y, 8);
    
    ofFill();
    ofSetColor(255, 255, 255, 120);
    ofCircle(position.x, position.y, 4);
    if (!on) ofNoFill();
    ofSetColor(color, 180);
    ofCircle(position.x, position.y, 4);
    
    ofPopStyle();
    
}

//----------------------------------------------------------------
void noToursWalker::update(Map& _map) {
    for (int i=0; i<path.size(); i++) {
        path[i].updatePosition(_map);
        if ((type=="stored")&&(i>=n)) {
                position.setPosition(path[i]);
            break;
        }
    }
    if (type=="live") position.updatePosition(_map);
    /*
    if ((type=="stored")&&(n<data.size())) {
        timer = 1000;
        int val = data.size() - 1 - n;
        if (data[val] != "") {
            vector<string> dataList = ofSplitString(data[val], ",");
            if ((dataList.size() == 3)&&(dataList[0] != "")&&(dataList[1] != "")&&(dataList[2] != "")) {
                position.setLocation(dataList[0],dataList[1]);
                path.push_back(VHPpoint(dataList[0],dataList[1]));
                time = dataList[2];
            }
        }
    } else {
        // cout << this.timer << endl;
    }
     */
    //if ((position.lat!=0)&&(position.lon!=0)) position.updatePosition(_map);
}

//----------------------------------------------------------------
void noToursWalker::addLocation(string _lat, string _long) {
    position.setLocation(_lat, _long);
    path.push_back(VHPpoint(_lat, _long));
    timer = 1000;
    /*
    cout << "path:" << endl;
    for (int i=0; i<=(path.size()-2); i++) {
        cout << "(" << path[i].x << ", " << path[i].y <<")" << endl;
        cout << "(" << path[i].lat << ", " << path[i].lon <<")" << endl;
    }
    */
}

void noToursWalker::addData(string _data) {
    data = ofSplitString(_data, ";");
    cout << "data: " << data.size() << endl;
    if (data.size()>=1) {
        for (int i=0; i<data.size(); i++) {
            vector<string> d = ofSplitString(data[i], ",");
            if ((d.size() == 3)&&(d[0] != "")&&(d[1] != "")&&(d[2] != "")) {
                //cout << "d: " << d[0] << ", " << d[1] << ", " << d[2] << endl;
                path.push_back(VHPpoint(d[0],d[1]));
            }
        }
    }
}

void noToursWalker::changeLevel(string _level) {
    if (_level!="") {
        level = ofToInt(_level);
        level_txt = "level "+ _level;
        //cout << "level = " << _level << endl;
        if (level==1) {
            trigger = false;
            triggered = false;
        }
    }
}

void noToursWalker::changeTrigger(string _trigger) {
    if ((_trigger=="1")&&(level>=2)) {
        trigger = true;
        //cout << "trigger = true" << endl;
    }
}

void noToursWalker::clean(Location& _max, Location& _min) {
    vector<VHPpoint> oldPath = path;
    path.clear();
    string txt = "";
    if (oldPath.size()>=1) {
        for (int i=0; i<oldPath.size(); i++) {
            if ((oldPath[i].lat>_max.lat)||(oldPath[i].lat<_min.lat)||(oldPath[i].lon<_max.lon)||(oldPath[i].lon>_min.lon)) {
                //cout << "point: " << oldPath[i].lat << ", " << oldPath[i].lon << endl;
            } else {
                //txt += ofToString(oldPath[i].lat) +", "+ ofToString(oldPath[i].lon) +" - ";
                path.push_back(oldPath[i]);
            }
        }
    }
    //cout << txt << endl;
}

//----------------------------------------------------------------
/*
void noToursWalker::checkCircles(noToursRssData& _project) {
    if (on) _project.checkCircles(x, y);
}
*/
//----------------------------------------------------------------
void noToursWalker::countDown() {
    timer--;
}
void noToursWalker::move() {
    n++;
}

//----------------------------------------------------------------
string noToursWalker::getData() {
    return "w "+ ofToString(id) +":"+ ofToString(position.x) +":"+ ofToString(position.y) +": ";
}

//----------------------------------------------------------------
float noToursWalker::near(float _a, float _b, int _p) {
    return _a + ((_b - _a)/200.0) * (float)_p;
}

//----------------------------------------------------------------

bool noToursWalker::over(float _x, float _y) {
    cout << "over x="+ ofToString(position.x) +" y="+ ofToString(position.y) << endl;
    return (_x > position.x - 12 && _x < position.x + 12 && _y > position.y - 12 && _y < position.y + 12);
}

bool noToursWalker::click(float _x, float _y) {
    if(over(_x, _y)) {
        on = !on;
        cout << "walker_id="+ ofToString(id) +" clicked" << endl;
        return true;
    }
    return false;
}

bool noToursWalker::checkOver(float _x, float _y) {
    return over(_x, _y);
}

//----------------------------------------------------------------	