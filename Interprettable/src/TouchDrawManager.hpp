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
    
    string saveToImage();
    vector<ofPolyline*> lines;

private:
    
    int currentLineId;
    
    ofFbo fbo;
    ofPixels pixels;

};

#endif /* TouchDrawManager_hpp */
