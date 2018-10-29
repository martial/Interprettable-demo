//
//  TouchDrawManager.hpp
//  TouchDrawTest
//
//  Created by Martial Geoffre-Rouland on 29/10/2018.
//

#ifndef TouchDrawManager_hpp
#define TouchDrawManager_hpp

#include "ofMain.h"

class TouchDrawManager {
  
public:
    
    void setup();
    void update();
    void draw();
    
    void clear();
    void addLine();
    void addPointToCurrent(ofPoint pnt);
    
    void drawPolyineThickWZ( ofPolyline * line);
    void drawPolyineThick( ofPolyline * line, int thickness);
    
private:
    
    vector<ofPolyline*> lines;
    int currentLineId;
};

#endif /* TouchDrawManager_hpp */
