#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    
    ofEnableAlphaBlending();
    ofEnableSmoothing();
    ofSetCircleResolution(64);
    
    //old OF default is 96 - but this results in fonts looking larger than in other programs.
	ofTrueTypeFont::setGlobalDpi(72);
    
    font1 = new ofTrueTypeFont;
    font1->loadFont("helveticaneueitalic.ttf", 10, false, true);
    font2 = new ofTrueTypeFont;
    font2->loadFont("helveticaneue.ttf", 12, false, true);
    
    // lee os settings do xml
    // settings
    if( settings.loadFile("settings.xml") ){
        cout << "mySettings.xml loaded from documents folder!" << endl;
        projects.setOSC(settings.getValue("OSC", false), settings.getValue("HOST", "localhost"), settings.getValue("PORT", 8000));
        int n = settings.getNumTags("PROJECT");
        for(int i = 0; i < n; i++){
            settings.pushTag("PROJECT", i);
            int id = settings.getValue("ID", 0);
            int zoom = settings.getValue("ZOOM", 0);
            string svg = settings.getValue("SVG", "");
            settings.pushTag("NW");
            string nw_lat = settings.getValue("LATITUDE", "0.0");
            string nw_lng = settings.getValue("LONGITUDE", "0.0");
            settings.popTag();
            settings.pushTag("SE");
            string se_lat = settings.getValue("LATITUDE", "0.0");
            string se_lng = settings.getValue("LONGITUDE", "0.0");
            settings.popTag();
            settings.pushTag("BUTTON");
            string name = settings.getValue("NAME", "");
            int x = settings.getValue("X", 0);
            int y = settings.getValue("Y", 0);
            int ox = settings.getValue("OX", 0);
            int oy = settings.getValue("OY", 0);
            settings.popTag();
            settings.popTag();
            cout << " " << endl;
            projects.addProject(id, zoom, ofToDouble(nw_lat), ofToDouble(nw_lng), ofToDouble(se_lat), ofToDouble(se_lng), svg, font1);
            projects.addButton(x, y, false, name, ox, oy, font2);
        }
    } else{
        cout << "unable to load settings.xml check data/ folder" << endl;
    }
    projects.loadProjects();
    
    logo.loadImage("logo-notours.png");
    
    /*
    
    // open an outgoing connection to HOST:PORT
    sender = new ofxOscSender;
	sender->setup(HOST, PORT);
    
    */
}

//--------------------------------------------------------------

void ofApp::init() {
    /*
    ofxOscMessage m;
    m.setAddress("/tech");
    m.addStringArg("start");
    sender->sendMessage(m);
     */
}

//--------------------------------------------------------------
void ofApp::update(){
    projects.update();
}

//--------------------------------------------------------------

void ofApp::draw(){
    ofBackground(0,0,0);
    projects.draw();
    logo.draw(60, 60);
}

//--------------------------------------------------------------

void ofApp::keyPressed(int key){
    projects.keyPressed(key);
}

//--------------------------------------------------------------

void ofApp::keyReleased(int key){
    projects.keyReleased(key);
}

//--------------------------------------------------------------

void ofApp::mouseMoved(int x, int y ){
    projects.mouseMoved(x, y);
}

//--------------------------------------------------------------

void ofApp::mouseDragged(int x, int y, int button){
    projects.mouseDragged(x, y, button);
}

//--------------------------------------------------------------

void ofApp::mousePressed(int x, int y, int button){
    projects.mousePressed(x, y, button);
}

//--------------------------------------------------------------

void ofApp::mouseReleased(int x, int y, int button){
    projects.mouseReleased(x, y, button);
}

//--------------------------------------------------------------

void ofApp::windowResized(int w, int h){
    projects.windowResized(w, h);
}

//--------------------------------------------------------------

void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------

void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
