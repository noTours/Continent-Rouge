#include "noToursWalker.h"

//constructor

//----------------------------------------------------------------	
noToursWalker::noToursWalker() {
}
noToursWalker::noToursWalker(int _id, int _project_id) {
    id = _id;
    project_id = _project_id;
    triggered = false;
    trigger = false;
    level = 1;
    last = 0;
    lasTriggered = 0;
}

// methods

//----------------------------------------------------------------

void noToursWalker::info() {
    cout << "id: " << id << ", project_id: " << project_id << ", level: " << level << ", trigger: " << trigger << ", triggered: " << triggered << endl;
}

string noToursWalker::getData() {
    return "walker: "+ ofToString(id) + ", project_id: "+ ofToString(project_id) + ", level: "+ ofToString(level) + ", trigger: "+ ofToString(trigger) + ", triggered: "+ ofToString(triggered);
}

//----------------------------------------------------------------

void noToursWalker::setLast(string _l, int _reset) {
    if (_l!="") {
        last = ofToInt(_l);
        int dif = last - lasTriggered;
        cout << "id: " << id << ", _l:" << _l << ", last:" << last << ", dif:" << dif << endl;
        if (dif>_reset) {
            cout << "reset triggered" << endl;
            triggered = false;
        }
    }
}

void noToursWalker::setLasTriggered() {
    lasTriggered = last;
}

void noToursWalker::changeLevel(string _level) {
    if (_level!="") {
        level = ofToInt(_level);
        if (level==1) {
            trigger = false;
            triggered = false;
        }
    }
}

void noToursWalker::changeTrigger(string _trigger) {
    if ((_trigger=="1")&&(level>=2)) {
        trigger = true;
    }
}

//----------------------------------------------------------------