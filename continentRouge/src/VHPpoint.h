#ifndef VHP_POINT
#define VHP_POINT

#include "ofMain.h"
#include "Map.h"

//--------------------------------------------------------
class VHPpoint {
    
    public:
    
        //constructor
        VHPpoint();
        VHPpoint(const float _x, const float _y, const std::string& _lat, const std::string& _lon);
        VHPpoint(const VHPpoint& _point);
        VHPpoint(const Location& _location);
        VHPpoint(const Point2d& _point);
        VHPpoint(const std::string& _lat, const std::string& _lon);
    
        // variables
        float x, y;
        double lat, lon;
        
        // methods
    
        void setPosition(float _x, float _y);
        void setPosition(const VHPpoint& _p);
        void setPositionX(float _x);
        void setPositionY(float _y);
    
        void setLocation(std::string _lat, std::string _lon);
    
        float distance(const VHPpoint& _p) const;
        float distance(float _x, float _y) const;
        float squareDistance(const VHPpoint& _p) const;
        float squareDistance(float _x, float _y) const;
    
        VHPpoint  operator*(const float _f) const;
        VHPpoint& operator-=(const VHPpoint& _p);
    
        double string_to_double(const std::string& _s);
    
        void updatePosition(Map &_map);
    
    private:
	
};
//--------------------------------------------------------

#endif 