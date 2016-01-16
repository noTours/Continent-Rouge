#pragma once

#include "ofMain.h"
#include "ofxXmlSettings.h"
#include "VHProundedButton.h"
#include "VHPhttpJson.h"

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
    
        vector<VHProundedButton> buttons;
		
        ofTrueTypeFont *        font1;
        ofTrueTypeFont *        font2;
    
        // Json
        VHPhttpJson             streamer;
    
        // settings
        ofxXmlSettings          settings;
};
