#ifndef NOTOURS_LOCATION
#define NOTOURS_LOCATION

#include "ofMain.h"
#include "Map.h"
#include "OpenStreetMapProvider.h"
#include "ofxOsc.h"
#include "ofxHttpUtils.h"
#include "noToursProject.h"
#include "noToursSoundPoint.h"
#include "noToursWalker.h"
#include "VHPpoint.h"
#include "VHPshape.h"
#include "VHPgetJson.h"
#include "VHPsendOSC.h"

//--------------------------------------------------------
class noToursLocation {
    public:
    
        //constructor
        noToursLocation();
        noToursLocation(int _id, int _zoom, double _lat1, double _long1, double _lat2, double _long2, string _shape, ofTrueTypeFont * _TTF, ofxHttpUtils * _http, VHPsendOSC * _osc);
    
        // variables
        int                             project_id;
        int                             zoom;
        string                          title;
        string                          description;
        int                             levels;
    
        // Sound Areas
        vector<noToursSoundPoint>       points;
        vector<int>                     milestones;
        int                             arrival_milestone;
    
        // Walkers
        VHPgetJson                      getWalkers;
        vector<noToursWalker>           walkers;
        vector<VHPpoint>                activeWalkers;
        vector<VHPpoint>                allWalkers;
        bool                            hasWalkers;
    
        Map                             map;
    
        bool                            loaded;
    
    
        VHPshape drawing;
        
        int timer;
    
        ofTrueTypeFont * font1;
    
        // sender
        VHPsendOSC * OSC;
    
        // methods
        void loadRSS(ofxXmlSettings _rss);
        void setGetWalkers(ofxHttpUtils * _http);
        void addWalker(noToursWalker _w);
        void addWalker(ofxJSONElement& _w);
        void addStoredWalker(ofxJSONElement& _w);
    
        void update();
        void updateCircles();
        void updateWalkers();
    
        void draw();
        void drawCircles(int _t);
        void drawWalkers(int _t);
    
        void checkChanges();
        void send(int _i);
    
        void mousePressed(int _x, int _y, int _button);
        void mouseReleased(int _x, int _y, int _button);
        void clickCircles(int _x, int _y);
        void updateActiveWalkers();
        void checkCirclesActive();
        void checkArrivalActive();
        // void checkMilestonesActive();
        // void checkArrivalCircleActive();
    
    private:
	
};
//--------------------------------------------------------

#endif 