#include "noToursLocation.h"

//constructor

//----------------------------------------------------------------	
noToursLocation::noToursLocation() { 
}
/*
noToursLocation::noToursLocation(int _id, ofxXmlSettings _rss, double _lat1, double _long1, double _lat2, double _long2, string _shape, ofTrueTypeFont * _TTF, ofxOscSender * _s) {
    sender = _s;
    //project.setSender(_s);
    author = noToursProject(_TTF);
    //storedAuthor = noToursProject(_TTF);
}*/
noToursLocation::noToursLocation(int _id, int _zoom, double _lat1, double _long1, double _lat2, double _long2, string _shape, ofTrueTypeFont * _TTF, ofxHttpUtils * _http, VHPsendOSC * _osc) {
    project_id = _id;
    zoom = _zoom;
    drawing = VHPshape();
    drawing.setLocation(_lat1, _long1, _lat2, _long2);
    drawing.loadShape(_shape);
    setGetWalkers(_http);
    OSC = _osc;
    loaded = false;
    hasWalkers = true;
    font1 = _TTF;
}

// methods

//----------------------------------------------------------------	

void noToursLocation::loadRSS(ofxXmlSettings _rss){
    // Title
    title = _rss.getValue("title", "");
    cout << "Title: " << title << endl;
    // Description
    description = _rss.getValue("description", "");
    cout << "Description: " << description << endl;
    // Map
    vector<string> center = ofSplitString(_rss.getValue("georss:point", ""), " ");
    Location location;
    (center.size()==2) ? location = Location(ofToFloat(center[0]), ofToFloat(center[1])) : location = Location(0.0, 0.0);
    map.setup(new OpenStreetMapProvider(), (double)ofGetWidth(), (double)ofGetHeight());
    map.setCenterZoom(location, zoom);
    cout << "zoom: " << zoom << " location: " << center[0] << " " << center[1] << endl;
    // Soundwalk Items
    int n = _rss.getNumTags("item");
    cout << "Número de áreas: " << n << endl;
    arrival_milestone = 0;
    for(int i=0; i<n; i++) {
        _rss.pushTag("item", i); // change relative root to <item>
        points.push_back(noToursSoundPoint());
        int l = (points.size() - 1);
        points[l].setTitle(_rss.getValue("title", ""));
        points[l].setDescription(_rss.getValue("description", ""));
        if (points[l].description=="arrival_point") {
            arrival_milestone = n;
            points[l].setArrival(1);
            cout << "Arrival_point: " << points[l].title << ", " << points[l].description << ", " << l << ", " << n << endl;
        }
        points[l].parseGeorssData(ofSplitString(_rss.getValue("georss:circle", ""), " "));
        if (_rss.tagExists("notours:soundpoint")) {
            _rss.pushTag("notours:soundpoint"); // change relative root to <notours:soundpoint>
            points[l].setAttributes(ofSplitString(_rss.getValue("notours:attributes", ""), " "));
            points[l].setLevel(ofToInt(_rss.getValue("notours:level", "")));
            points[l].setMilestone(ofToInt(_rss.getValue("notours:milestone", "")));
            if (points[l].milestone!=0) {
                milestones.push_back(l);
                cout << "Milestone: " << l << " level - " << points[l].milestone << endl;
            }
            if (_rss.tagExists("notours:soundsource")) {
                _rss.pushTag("notours:soundsource"); // change relative root to <notours:soundpoint>
                points[l].setSoundPath(_rss.getValue("notours:file", ""));
                _rss.popTag();
            }
            _rss.popTag();
        }
        _rss.popTag();
    }
    loaded = true;
}

//----------------------------------------------------------------

void noToursLocation::setGetWalkers(ofxHttpUtils * _http) {
    getWalkers.setUrl("http://www.editor.notours.org/exec/walker_coordinates.php");
    getWalkers.setHttpUtils(_http);
    getWalkers.setInterval(200);
    getWalkers.addField("project_id", ofToString(project_id));
    getWalkers.addField("last", "true");
    getWalkers.addField("auth_key", "04031948");
}

//----------------------------------------------------------------

void noToursLocation::addWalker(noToursWalker _w) {
    walkers.push_back(_w);
    hasWalkers = true;
}
void noToursLocation::addWalker(ofxJSONElement& _w) {
    int w_id = ofToInt(_w["walker_id"].asString());
    //cout << "walker id: " << w_id <<endl;
    bool added = false;
    //cout << "noToursProject has " << walkers.size() << " walker" <<endl;
    if (hasWalkers==true) {
        for (int i=0; i<walkers.size(); i++) {
            if (walkers[i].id == w_id) {
                walkers[i].addLocation(_w["latitude"].asString(), _w["longitude"].asString());
                walkers[i].changeLevel(_w["level"].asString());
                walkers[i].changeTrigger(_w["trigger"].asString());
                cout << "trigger " << walkers[i].trigger << " triggered " << walkers[i].triggered << " level " << walkers[i].level << endl;
                //cout << "New location data (" << _w["latitude"].asString() << "," << _w["longitude"].asString() << ") added to an existing walker" <<endl;
                added = true;
                break;
            }
        }
    }
    if (!added) {
        string project_id = _w["project_id"].asString();
        string latitude = _w["latitude"].asString();
        string longitude = _w["longitude"].asString();
        string time = _w["time"].asString();
        if ((project_id!="")&&(latitude!="")&&(longitude!="")&&(time!="")) {
            addWalker(noToursWalker(w_id, ofToInt(_w["project_id"].asString()), _w["latitude"].asString(), _w["longitude"].asString(), _w["time"].asString(), font1));
            //cout << "New walker created" <<endl;
        }
    }
}

//----------------------------------------------------------------

void noToursLocation::addStoredWalker(ofxJSONElement& _w) {
    addWalker(noToursWalker(ofToInt(_w["walker_id"].asString()), ofToInt(_w["project_id"].asString()), _w["data"].asString(), font1));
}


//----------------------------------------------------------------

void noToursLocation::update() {
    
    getWalkers.update();
    map.update();
    drawing.updatePosition(map);
    
    updateCircles();
    
    //storedAuthor.updateProjects(map);
    //author.updateProjects(map);
    updateWalkers();
    //author.updateActiveWalkers();
    
    
}

//----------------------------------------------------------------

void noToursLocation::updateCircles() {
    for (int i=0; i<points.size(); i++) {
        points[i].updatePosition(map);
        points[i].updateSound();
    }
}

//----------------------------------------------------------------
void noToursLocation::updateWalkers() {
    if(hasWalkers) {
        for(int i=0; i<walkers.size(); i++){
            walkers[i].update(map);
        }
    }
}

//----------------------------------------------------------------

void noToursLocation::draw() {
    
    ofPushStyle();
    ofNoFill();
    ofSetColor(220, 250, 220, 120);
    ofSetLineWidth(1.3);
    drawing.draw();
    ofPopStyle();
    
    
    int t = ofGetFrameNum()%20;
    drawCircles(t);
    drawWalkers(t);
    
    //storedAuthor.drawProjectWalkers(timer);
    //author.drawProjectWalkers(timer);
    // if (start) map.draw();
}

//----------------------------------------------------------------

void noToursLocation::drawCircles(int _t) {
    for (int i=0; i<points.size(); i++) {
        //if (i==project.arrival_milestone)
        points[i].draw();
    }
}

//----------------------------------------------------------------
void noToursLocation::drawWalkers(int _t) {
    if(hasWalkers) {
        for (int i=0; i<walkers.size(); i++) {
            walkers[i].draw(_t);
            //if (i<= 30) break;
        }
    }
}

//----------------------------------------------------------------

void noToursLocation::checkChanges() {
    updateActiveWalkers();
    checkCirclesActive();
    checkArrivalActive();
    // checkMilestonesActive();
    // checkArrivalCircleActive();
}

void noToursLocation::send(int _i) {
    ofxOscMessage msg;
    msg.setAddress("/walker");
    /*if (_i == 1) {
        msg.addStringArg("totem1");
        msg.addIntArg(1);
    } else if (_i == 2) {
        msg.addStringArg("totem2");
        msg.addIntArg(2);
    } else if (_i == 3) {
        msg.addStringArg("totem3");
        msg.addIntArg(3);
    } else if (_i == 4) {
        msg.addStringArg("totem4");
        msg.addIntArg(4);
    } else if (_i == 5) {
        msg.addStringArg("totem5");
        msg.addIntArg(5);
    }*/
    /*
    msg.addStringArg(author.walkers[_i].milestone);
    msg.addIntArg(author.walkers[_i].id);
     */
    //sender->sendMessage(msg);
}

//----------------------------------------------------------------

void noToursLocation::mousePressed(int _x, int _y, int _button) {
    map.mousePressed(_x, _y, _button);
}

//--------------------------------------------------------------

void noToursLocation::mouseReleased(int _x, int _y, int _button) {
    //storedAuthor.clickCircles(_x, _y);
    //author.clickCircles(_x, _y);
    clickCircles(_x, _y);
    map.mouseReleased(_x, _y, _button);
}

//----------------------------------------------------------------

void noToursLocation::clickCircles(int _x, int _y) {
    if (hasWalkers) {
        for(int i=0; i<walkers.size(); i++) {
            if (walkers[i].click(_x, _y)) {
                break;
            }
        }
    }
}

//----------------------------------------------------------------

void noToursLocation::updateActiveWalkers() {
    if (hasWalkers) {
        activeWalkers.clear();
        allWalkers.clear();
        //cout << "activeWalkers.clear();" << endl;
        for(int i=0; i<walkers.size(); i++) {
            if (walkers[i].on) {
                activeWalkers.push_back(walkers[i].position);
                //cout << "activeWalkers.push_back(walkers["+ ofToString(i) +"].position);" << endl;
            }
            allWalkers.push_back(walkers[i].position);
        }
    }
}

//----------------------------------------------------------------

void noToursLocation::checkCirclesActive() {
    for (int i=0; i<points.size(); i++) {
        if (!points[i].playing) {
            // cout << " activeWalkers.size() " << activeWalkers.size();
            for (int u=0; u<activeWalkers.size(); u++) {
                cout << "activeWalkers xy " << activeWalkers[u].x << " " << activeWalkers[u].y << endl;
                if (points[i].checkOver(activeWalkers[u].x, activeWalkers[u].y)) {
                    cout << "points["+ ofToString(i) +"].playing()";
                    OSC->addMsg(points[i].play());
                    break;
                }
            }
            cout << "." << endl;
        } else {
            bool stp = false;
            //cout << "points["+ ofToString(i) +"] is playing" << endl;
            for (int u=0; u<activeWalkers.size(); u++) {
                if (points[i].checkOver(activeWalkers[u].x, activeWalkers[u].y)) {
                    //cout << "_aWalkers.size()="+ofToString(_aWalkers.size()) << endl;
                    //cout << "stp = true;" << endl;
                    stp = true;
                }
            }
            if (!stp) {
                cout << "points["+ ofToString(i) +"].stop()" << endl;
                OSC->addMsg(points[i].stop());
            }
        }
    }
}

//----------------------------------------------------------------

void noToursLocation::checkArrivalActive() {
    if (hasWalkers) {
        for (int i=0; i<walkers.size(); i++) {
            if ((walkers[i].trigger==true)&&(walkers[i].triggered==false)) {
                /*
                 cout << "osc trigger " << endl;
                 ofxOscMessage msg;
                 msg.setAddress("/walker");
                 msg.addStringArg("totem"+ofToString(_walkers[i].level));
                 msg.addIntArg(_walkers[i].level);
                 sender->sendMessage(msg);
                 */
                walkers[i].triggered = true;
            }
        }
    }
}

//----------------------------------------------------------------
/*
void noToursLocation::checkMilestonesActive() {
    
}
*/
//----------------------------------------------------------------
/*
void noToursLocation::checkArrivalCircleActive() {
    
}
*/
//----------------------------------------------------------------