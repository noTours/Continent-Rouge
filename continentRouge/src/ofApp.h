#pragma once

#include "ofMain.h"

#include "ofxXmlSettings.h"
#include "noToursProjects.h"

#define HOST "localhost"
#define PORT 8000

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
    
        void init();
    
        // settings
        ofxXmlSettings          settings;
    
        // noTours Projects
        noToursProjects         projects;
    
        // Fonts
        ofTrueTypeFont *        font1;
        ofTrueTypeFont *        font2;
    
        // noTours Logo
        ofImage logo;
    
    /*
        ofxOscSender * sender;
    
     */
    
};
