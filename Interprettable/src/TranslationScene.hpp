//
//  TranslationScene.hpp
//  Interprettable
//
//  Created by Martial Geoffre-Rouland on 30/10/2018.
//

#pragma once

#include "ofMain.h"
#include "AbstractScene.hpp"
#include "ofxBox2d.h"
#include "ofxFontStash2.h"
#include "ofxOpenCv.h"

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
    
    ofxBox2d                               box2d;   // the box2d world
    vector   <shared_ptr<ofxBox2dRect> >   boxes;   // defalut box2d rects
    vector <shared_ptr<ofxBox2dPolygon>>   polyShapes;

    ofTrueTypeFont                          font;
    ofxFontStash2::Style                    box2dStyle;
    
    
    ofxCvColorImage          colorImg;
    ofxCvGrayscaleImage     grayImage;
    ofxCvContourFinder     contourFinder;
    
    ofJson languagesJson;
    int currentLanguage;
};

