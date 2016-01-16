#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofSetFrameRate(10);
    
    // lee os settings do xml
    settings.loadFile("settings.xml");
    streamer.init(settings.getValue("URL", "http://www.editor.notours.org/exec/walker_coordinates.php"), "true", settings.getValue("PROJECT","1083"), "04031948", settings.getValue("HOST", "localhost"), settings.getValue("PORT", 8000), settings.getValue("RESET", 60));
    cout << "project: " << streamer.project_id << endl;
    
    logo.loadImage("logo-notours.png");
    loadded = true;
    streamer.start();
    
}

//--------------------------------------------------------------
void ofApp::update(){
    streamer.update();
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofBackground(0,0,0);
    logo.draw(60, 60);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
    if (key == '0' ) {
        //activeLocation = 0;
    } else if (key == '1' ) {
        streamer.send(1);
        //activeLocation = 1;
    } else if (key == '2' ) {
        streamer.send(2);
        //activeLocation = 2;
    } else if (key == '3' ) {
        streamer.send(3);
        //activeLocation = 3;
    } else if (key == '4' ) {
        streamer.send(4);
        //activeLocation = 3;
    } else if (key == '5' ) {
        streamer.send(5);
        //activeLocation = 3;
    }
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

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

//--------------------------------------------------------------