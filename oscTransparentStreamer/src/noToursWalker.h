#ifndef NOTOURS_WALKER
#define NOTOURS_WALKER

#include "ofMain.h"

//--------------------------------------------------------
class noToursWalker {
    public:
    
        //constructor
        noToursWalker();
        noToursWalker(int _id, int _project_id);
    
        // variables
        int id;
        int project_id;
        bool triggered;
        bool trigger;
        int level;
        int last;
        int lasTriggered;
    
        // methods
    
        void info();
        string getData();
        void setLast(string _l, int _reset);
        void setLasTriggered();
        void changeLevel(string _level);
        void changeTrigger(string _trigger);
    
    private:
	
};
//--------------------------------------------------------

#endif 