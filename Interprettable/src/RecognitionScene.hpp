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
#include "InteractiveButton.hpp"

class RecognitionScene : public AbstractScene {
    
public:
    
    RecognitionScene(){ };
    
    void init();
    void setup();
    void prepass();
    
    void mouseDragged(int x, int y, int button);
    void mousePressed(int x, int y, int button);
    void mouseReleased(int x, int y, int button);;
    
    void onClearButtonClickedEventHandler(ofEventArgs & e);
    
private:
    
    ofImage backgroundImage;
    
    ofImage maskImage;
    ofxMask *drawingMask;
    
    TouchDrawManager touchDrawManager;
    
    InteractiveButton clearButton;
};

