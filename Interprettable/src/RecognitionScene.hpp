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
#include "ofxOsc.h"

class RecognitionScene : public AbstractScene {
    
public:
    
    RecognitionScene(){ };
    
    void init();
    void setup();
    void update();
    void prepass();
    
    void mouseDragged(int x, int y, int button);
    void mousePressed(int x, int y, int button);
    void mouseReleased(int x, int y, int button);;
    
    void onClearButtonClickedEventHandler(ofEventArgs & e);
    
private:
    
    string caption;
    ofImage backgroundImage;
    
    ofImage maskImage;
    ofxMask *drawingMask;
    
    TouchDrawManager touchDrawManager;
    InteractiveButton clearButton;
    
    ofxOscReceiver osc;
    ofxOscSender sender;
};

