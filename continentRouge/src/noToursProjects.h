#ifndef NOTOURS_PROJECTS
#define NOTOURS_PROJECTS

#include "ofMain.h"
#include "Map.h"
#include "ofxXmlSettings.h"
#include "noToursLocation.h"
#include "VHProundedButton.h"
#include "ofxHttpUtils.h"
#include "VHPsendOSC.h"

//--------------------------------------------------------
class noToursProjects {
    public:
    
        //constructor
        noToursProjects();
        
        // variables
        vector<noToursLocation>         locations;
        vector<VHProundedButton>        buttons;
        int                             activeLocation;
        bool                            locationsloaded;
        ofxHttpUtils *                  loadRSS;
        ofxHttpUtils *                  loadWalkers;
        VHPsendOSC *                    OSC;
    
        // methods
        void addProject(int _id, int _zoom, double _lat1, double _long1, double _lat2, double _long2, string _shape, ofTrueTypeFont * _TTF);
        void addButton(float _x, float _y, bool _a, string _text, float _ofsetx, float _ofsety, ofTrueTypeFont * _TTF);
        void loadProjects();
        void setOSC(bool _s, string _host, int _port);
        void readRSS(ofxHttpResponse& response);
        void readJson(ofxHttpResponse& response);
        void startGetWalkers();
        void update();
        void draw();
    
        void keyPressed(int key);
        void keyReleased(int key);
        void mouseMoved(int x, int y);
        void mouseDragged(int _x, int _y, int _button);
        void mousePressed(int _x, int _y, int _button);
        void mouseReleased(int _x, int _y, int _button);
        void windowResized(int w, int h);
    
    private:
	
};
//--------------------------------------------------------

#endif 