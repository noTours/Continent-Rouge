#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    
    ofEnableAlphaBlending();
    ofEnableSmoothing();
    ofSetCircleResolution(64);

    font1 = new ofTrueTypeFont;
    font1->loadFont("helveticaneueitalic.ttf", 10, false, true);
    font2 = new ofTrueTypeFont;
    font2->loadFont("helveticaneue.ttf", 12, false, true);
    
    // lee os settings do xml
    settings.loadFile("settings.xml");
    
    buttons.push_back(VHProundedButton(20, 20, false, "Sierra", 38, 12, font2));
    buttons.push_back(VHProundedButton(140, 20, false, "Artaud", 38, 12, font2));
    buttons.push_back(VHProundedButton(260, 20, false, "Erasmo", 38, 12, font2));
    
    // Json
    streamer.init(settings.getValue("SEND_URL_1", "http://www.editor.notours.org/exec/update_walker.php"), settings.getValue("SEND_URL_2", "http://www.editor.notours.org/exec/update_trigger.php"), settings.getValue("USER", "triggerSenderApp"), settings.getValue("MAC", "000000000000000"), settings.getValue("LATITUDE", "0.0"), settings.getValue("LONGITUDE", "0.0"), settings.getValue("PROJECT", "1083"), "04031948");
    streamer.start();
}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){
    ofBackground(0,0,0);
    for (int i=0; i<buttons.size(); i++) {
        buttons[i].display();
    }
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
    for (int i=0; i<buttons.size(); i++) {
        if (buttons[i].over(x,y)) {
            if (!buttons[i].active) {
                buttons[i].set(true);
                streamer.sendData(i);
            }
            break;
        }
    }
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){
    for (int i=0; i<buttons.size(); i++) {
        if (buttons[i].active) {
            buttons[i].set(false);
            break;
        }
    }
}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
