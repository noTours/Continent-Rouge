#include "VHPgetJson.h"

//constructor

//----------------------------------------------------------------	
VHPgetJson::VHPgetJson() {
    interval = 20;
}

// methods

//----------------------------------------------------------------

void VHPgetJson::addField(string _field, string _value) {
    fields.push_back(_field);
    values.push_back(_value);
}

//----------------------------------------------------------------

void VHPgetJson::setUrl(string _url) {
    url = _url;
}

//----------------------------------------------------------------

void VHPgetJson::setHttpUtils(ofxHttpUtils * _http) {
    http = _http;
}

//----------------------------------------------------------------

void VHPgetJson::setInterval(int _t) {
    interval = _t;
}

//----------------------------------------------------------------

void VHPgetJson::update() {
    if (streaming) {
        timer++;
        if (timer>=interval) {
            getData();
            timer = 0;
        }
    }
}

//----------------------------------------------------------------

void VHPgetJson::getData() {
    ofxHttpForm form;
    form.action = url;
    form.method = OFX_HTTP_POST;
    for (int i=0; i<fields.size(); i++) {
        form.addFormField(fields[i], values[i]);
    }
    http->addForm(form);
}

//----------------------------------------------------------------

void VHPgetJson::start() {
    streaming = true;
}

//----------------------------------------------------------------

void VHPgetJson::stop() {
    streaming = false;
}

//----------------------------------------------------------------