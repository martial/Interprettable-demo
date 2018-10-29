//
//  AbstractScene.hpp
//  Interprettable
//
//  Created by Martial Geoffre-Rouland on 29/10/2018.
//

#ifndef AbstractScene_hpp
#define AbstractScene_hpp

#include "ofMain.h"

class AbstractScene {
  
public:
    
    virtual void setup();
    virtual void update();
    virtual void draw();
    
    virtual void init();
    virtual void quit();
    
    ofEventArgs quitFinishedEvent;
};

#endif /* AbstractScene_hpp */
