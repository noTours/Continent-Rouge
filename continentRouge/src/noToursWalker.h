#ifndef NOTOURS_WALKER
#define NOTOURS_WALKER

#include "ofMain.h"
#include "VHPpoint.h"   
//#include "noToursRssData.h"

//--------------------------------------------------------
class noToursWalker {
    public:
    
        //constructor
        noToursWalker();
        noToursWalker(int _id, int _project_id, string _lat, string _lon, string _time, ofTrueTypeFont * _TTF);
        noToursWalker(int _id, int _project_id, string _data, ofTrueTypeFont * _TTF);
    
        // variables
        int id;
        ofColor color;
        int timer;
        int project_id;
        bool triggered;
        bool trigger;
        int level;
        string level_txt;
        VHPpoint position;
        vector<VHPpoint> path;
        vector<string> data;
        string time;
        string type;
        int n;
        float x, y;
        bool on;
        // info
        ofTrueTypeFont * font;
    
        // methods
        void info();
        void draw(int _t);
        void drawPath();
        void drawPosition();
    
        void update(Map& _map);
        void addLocation(string _lat, string _lon);
        void addData(string _data);
        void changeLevel(string _level);
        void changeTrigger(string _trigger);
        void clean(Location& _max, Location& _min);
    
        //void checkCircles(noToursRssData& _project);
        void countDown();
        void move();
        string getData();
        float near(float _a, float _b, int _p);
    
        bool over(float _x, float _y);
        bool click(float _x, float _y);
        bool checkOver(float _x, float _y);
    
    private:
	
};
//--------------------------------------------------------

#endif 