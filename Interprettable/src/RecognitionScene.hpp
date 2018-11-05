//
//  RecognitionScene.hpp
//  Interprettable
//
//  Created by Martial Geoffre-Rouland on 05/11/2018.
//

#pragma once

#include "ofMain.h"
#include "AbstractScene.hpp"
#include "TouchDrawManager.hpp"

class RecognitionScene : public AbstractScene {
    
public:
    
    RecognitionScene(){ };
    
    void init();
    void setup();
    void prepass();
    
    void mouseDragged(int x, int y, int button);
    void mousePressed(int x, int y, int button);
    
private:
    
    ofImage backgroundImage;
    
    ofImage maskImage;
    ofxMask *drawingMask;
    
    TouchDrawManager touchDrawManager;

};

