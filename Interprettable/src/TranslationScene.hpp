//
//  TranslationScene.hpp
//  Interprettable
//
//  Created by Martial Geoffre-Rouland on 30/10/2018.
//

#pragma once

#include "ofMain.h"
#include "AbstractScene.hpp"

class TranslationScene : public AbstractScene {
    
public:
    
    TranslationScene(){ };
    
    void init();
    void setup();
    void prepass();
    
    void mousePressed(int x, int y, int button);
    
private:
    
    ofImage backgroundImage;
    
    ofImage maskImage;
    ofxMask *translationMask;
};

