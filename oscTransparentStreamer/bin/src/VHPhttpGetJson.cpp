#include "VHPhttpGetJson.h"

//constructor

//----------------------------------------------------------------	
VHPhttpGetJson::VHPhttpGetJson() {
}

// methods

//--------------------------------------------------------------

void VHPhttpGetJson::init(string _get_url, string _last, string _project_id, string _auth_key, string _host, int _port, int _reset) {
    
    get_url = _get_url;
    last = _last;
    project_id = _project_id;
    auth_key = _auth_key;
    streaming = false;
    timer = 0;
    reset = _reset;
    
    // open an outgoing connection to HOST:PORT
    sender = new ofxOscSender;
    sender->setup(_host, _port);
    cout << "OSC HOST: " << _host << " PORT: " << _port << endl;
    
    // add listener to httpUtils thread
    ofAddListener(httpUtils.newResponseEvent, this, &VHPhttpGetJson::newResponse);
    
}

//----------------------------------------------------------------

void VHPhttpGetJson::update() {
    timer++;
    if (timer>=20) {
        getData();
        timer = 0;
    }
}

//----------------------------------------------------------------

void VHPhttpGetJson::getData(){
    // cout << "getData();" << endl;
    ofxHttpForm form;
    form.action = get_url;
    form.method = OFX_HTTP_POST;
    form.addFormField("last", last);
    form.addFormField("project_id", project_id);
    form.addFormField("auth_key", auth_key);
    httpUtils.addForm(form);
}

//----------------------------------------------------------------

void VHPhttpGetJson::newResponse(ofxHttpResponse & _response){
    // cout << ofToString(response.status) << endl;
    // cout << _response.responseBody << endl;
    ofxJSONElement result;
    if (result.parse(_response.responseBody)) {
        bool error = result["error"].asBool();
        if (error) {
            if (result["error_type"].asString()=="3") {
                string msg = result["msg"].asString();
                cout << msg << endl;
            } else {
                string msg = result["error_msg"].asString();
                cout << msg << endl;
            }
        } else {
            // cout << "project " << result["id"].asString() << ":"<< endl;
            updateWalkers(_response.responseBody);
        }
        checkArrival(walkers);
    }
}

//----------------------------------------------------------------

void VHPhttpGetJson::updateWalkers(string _data) {
    ofxJSONElement json;
    if (json.parse(_data)) {
        string format = json["format"].asString();
        // cout << "Format: " << format << endl;
        if (json["data"].isString()) {
            cout << "Nobody walking at the moment" << endl;
            cout << "" << endl;
        } else {
            int nWalkers = json["data"].size();
            //cout << "Loadded " << nWalkers << " walkers" << endl;
            if (format=="byProjectId") {
                for (int i=0; i<nWalkers; i++) {
                    ofxJSONElement w = json["data"][i];
                    addWalker(w);
                }
            } else if (format=="last") {
                
            }
        }
    }
}

//----------------------------------------------------------------

void VHPhttpGetJson::addWalker(ofxJSONElement& _w) {
    int w_id = ofToInt(_w["walker_id"].asString());
    //cout << "walker id: " << w_id <<endl;
    bool added = false;
    //cout << "noToursProject has " << walkers.size() << " walker" <<endl;
    if (hasWalkers==true) {
        for (int i=0; i<walkers.size(); i++) {
            if (walkers[i].id == w_id) {
                walkers[i].changeLevel(_w["level"].asString());
                walkers[i].changeTrigger(_w["trigger"].asString());
                // cout << "miliseconds: " << _w["miliseconds"].asString() << endl;
                walkers[i].setLast(_w["miliseconds"].asString(), reset);
                walkers[i].info();
                cout << "" << endl;
                added = true;
                break;
            }
        }
    }
    if (!added) {
        string w_project_id = _w["project_id"].asString();
        if (project_id==w_project_id) {
            walkers.push_back(noToursWalker(w_id,ofToInt(project_id)));
            walkers[walkers.size()-1].changeLevel(_w["level"].asString());
            walkers[walkers.size()-1].changeTrigger(_w["trigger"].asString());
            walkers[walkers.size()-1].setLast(_w["miliseconds"].asString(), reset);
            hasWalkers = true;
            cout << "New walker created" <<endl;
            walkers[walkers.size()-1].info();
            cout << "" << endl;
        }
    }
}

//----------------------------------------------------------------

void VHPhttpGetJson::checkArrival(vector<noToursWalker> & _walkers) {
    for (int i=0; i<_walkers.size(); i++) {
        if ((_walkers[i].trigger==true)&&(_walkers[i].triggered==false)) {
            cout << "osc trigger " << endl;
            cout << "" << endl;
            ofxOscMessage msg;
            msg.setAddress("/walker");
            msg.addStringArg("totem"+ofToString(_walkers[i].level));
            msg.addIntArg(_walkers[i].level);
            sender->sendMessage(msg);
            _walkers[i].triggered = true;
            _walkers[i].setLasTriggered();
        }
    }
}

//----------------------------------------------------------------

void VHPhttpGetJson::send(int _i) {
    ofxOscMessage msg;
    msg.setAddress("/walker");
    if (_i == 1) {
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
    }
    sender->sendMessage(msg);
}

//----------------------------------------------------------------

void VHPhttpGetJson::start() {
    
    // start httpUtils thread & send first query
    cout << "VHPhttpJson.start();" << endl;
    httpUtils.start();
    streaming = true;
    getData();
    
    // send OSC start message 
    ofxOscMessage m;
    m.setAddress("/tech");
    m.addStringArg("start");
    sender->sendMessage(m);
}

//----------------------------------------------------------------

void VHPhttpGetJson::stop() {
    
    // stop httpUtils thread
    cout << "VHPhttpJson.stop();" << endl;
    httpUtils.stop();
    streaming = false;
    
    // send OSC stop message
    ofxOscMessage m;
    m.setAddress("/tech");
    m.addStringArg("stop");
    sender->sendMessage(m);
}

//----------------------------------------------------------------



