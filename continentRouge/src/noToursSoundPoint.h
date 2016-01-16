#ifndef NOTOURS_SOUNDPOINT
#define NOTOURS_SOUNDPOINT

#include "ofMain.h"
#include "ofxOsc.h"
#include "Map.h"
#include "noToursProject.h"

//--------------------------------------------------------
class noToursSoundPoint {
    public:
    
        //constructor
        noToursSoundPoint();
        noToursSoundPoint(string _lat, string _long, string _x, string _y, string _r, string _l);
        noToursSoundPoint(string _title, string _description, string _l, string _lat, string _long, string _r, vector<string> _a);
    
        // variables
        string title, description, soundPath;
        ofSoundPlayer sound;
        float volume;
        vector<string> attributes;
        int level;
        int milestone;
        int arrival;

        Location location, radiusLocation;
        float radius, screenRadius;
        Point2d position, radiusPosition;
    
        bool playing;
        bool stopping;
        bool moving;
        int playerStart;
    
        float grow_r;
        float grow_d;
    
        // methods
        void setTitle(string _title);
        void setDescription(string _description);
        void setSoundPath(string _path);
        void setAttributes(vector<string> _a);
        void setLevel(int _l);
        void setMilestone(int _m);
        void setArrival(int _a);
    
        void parseGeorssData(vector<string> _georssData);
        void updatePosition(Map& _map);
        double string_to_double(const std::string& _s);
        double getLongAtDistance(double _lat, double _long, float _dist);
    
        void drawSimple();
        void draw();
        float grow(float _a, const float& _p, float _r);
    
        ofxOscMessage play();
        ofxOscMessage stop();
        ofxOscMessage mgs(string _audio, int _playing);
        bool checkOver(float _x, float _y);
    
        // seound methods
        void fadeIn();
        void fadeOut();
        void updateSound();
    
    private:
	
};
//--------------------------------------------------------

#endif 