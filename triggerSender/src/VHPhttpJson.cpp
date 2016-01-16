#include "VHPhttpJson.h"

//constructor

//----------------------------------------------------------------	
VHPhttpJson::VHPhttpJson() {
}

// methods

//--------------------------------------------------------------

void VHPhttpJson::init(string _send_url_1, string _send_url_2, string _user_name, string _user_mac, string _latitude, string _longitude, string _project_id, string _auth_key) {
    send_url_1 = _send_url_1;
    send_url_2 = _send_url_2;
    user_name = _user_name;
    user_mac = _user_mac;
    project_id = _project_id;
    auth_key = _auth_key;
    latitude = _latitude;
    longitude = _longitude;
    streaming = true;
    ofAddListener(httpUtils.newResponseEvent, this, &VHPhttpJson::newResponse);
}

//----------------------------------------------------------------

void VHPhttpJson::update(string _user_name, string _data_name) {

}

//----------------------------------------------------------------

void VHPhttpJson::sendData(int _i){
    cout << "sendData: level = " << _i << ";" << endl;
    
    ofxHttpForm form1;
    form1.action = send_url_1;
    form1.method = OFX_HTTP_POST;
    form1.addFormField("auth_key",auth_key);
    form1.addFormField("name", user_name);
    form1.addFormField("mac", user_mac);
    form1.addFormField("project_id", project_id);
    form1.addFormField("latitude", latitude);
    form1.addFormField("longitude", longitude);
    
    ofxHttpForm form2;
    form2.action = send_url_2;
    form2.method = OFX_HTTP_POST;
    form2.addFormField("auth_key",auth_key);
    form2.addFormField("name", user_name);
    form2.addFormField("mac", user_mac);
    form2.addFormField("project_id", project_id);
    form2.addFormField("trigger", "1");
    form2.addFormField("level", ofToString(_i+2));
    
    httpUtils.addForm(form1);
    httpUtils.addForm(form2);
    
}

//----------------------------------------------------------------

void VHPhttpJson::newResponse(ofxHttpResponse & response){
    // cout << ofToString(response.status) << endl;
    ofxJSONElement result;
    result.parse(response.responseBody);
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
        if (result["process_id"].asString()=="exec_update_walker") {
            string d_id = result["data"]["id"].asString();
            string d_latitude = result["data"]["latitude"].asString();
            string d_longitude = result["data"]["longitude"].asString();
            string d_walker_id = result["data"]["walker_id"].asString();
            string d_project_id = result["data"]["project_id"].asString();
            string d_time = result["data"]["time"].asString();
            cout << "success to parse JSON after sending data: " << d_id << " latitude: " << d_latitude << " longitude: " << d_longitude << " walker_id: " << d_walker_id << " project_id: " << d_project_id << " time: " << d_time << endl;
        } else if (result["process_id"].asString()=="exec_update_trigger") {
            string d_id = result["data"]["id"].asString();
            string d_level = result["data"]["level"].asString();
            string d_trigger = result["data"]["trigger"].asString();
            string d_walker_id = result["data"]["walker_id"].asString();
            string d_project_id = result["data"]["project_id"].asString();
            string d_time = result["data"]["time"].asString();
            cout << "success to parse JSON after sending data: " << d_id << " level: " << d_level << " trigger: " << d_trigger << " walker_id: " << d_walker_id << " project_id: " << d_project_id << " time: " << d_time << endl;
        } else {
            cout << response.responseBody << endl;
        }
    }
    
}

//----------------------------------------------------------------

void VHPhttpJson::start() {
    cout << "VHPhttpJson: httpUtils.start()" << endl;
    httpUtils.start();
    streaming = true;
}

//----------------------------------------------------------------

void VHPhttpJson::stop() {
    cout << "VHPhttpJson: httpUtils.stop()" << endl;
    httpUtils.stop();
    streaming = false;
}

//----------------------------------------------------------------



