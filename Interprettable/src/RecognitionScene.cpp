//
//  RecognitionScene.cpp
//  Interprettable
//
//  Created by Martial Geoffre-Rouland on 05/11/2018.
//

#include "RecognitionScene.hpp"
#include "ofxImgSizeUtils.h"
#include "SceneManager.hpp"
#include "ofApp.h"

void RecognitionScene::setup() {
    
    
    touchDrawManager.setup();
    
    setIntroductionImage("scenes/recognition/Barcelone13.png");
    
    backgroundImage.load("scenes/recognition/background.jpg");
    
    drawingMask = new ofxMask();
    drawingMask->allocate(ofGetWidth(), ofGetHeight(), ofxMask::LUMINANCE);
    maskImage.load("scenes/recognition/mask.jpg");
    
    drawingMask->beginMask();
    ofSetColor(255);
    maskImage.draw(0.0,0.0);
    drawingMask->endMask();
    
    
}

void RecognitionScene::init() {
    
    AbstractScene::init();
    step = 0;
    
}


void RecognitionScene::prepass() {
    
    
    ofRectangle r;
    
    mask.begin();
    
    if (step == 0 ) {
        
        r = ofxImgSizeUtils::getCenteredRect(ofGetWidth(), ofGetHeight(), introductionImage.getWidth(), introductionImage.getHeight(), true);
        introductionImage.draw(r);
    }
    
    if (step == 1 ) {
        
        r = ofxImgSizeUtils::getCenteredRect(ofGetWidth(), ofGetHeight(), backgroundImage.getWidth(), backgroundImage.getHeight(), true);
        backgroundImage.draw(r);
        
        
        drawingMask->begin();
        
       // draw
        
        touchDrawManager.draw();

        
        drawingMask->end();
        
        drawingMask->draw();
        
        
        
    }
    
    
    mask.end();
    
    
    mask.draw();
    
}

void RecognitionScene::mousePressed(int x, int y, int button) {
    
    if(step == 0)
        step++;
    
    
    if(step == 1)
        touchDrawManager.addLine();
    
}

void RecognitionScene::mouseDragged(int x, int y, int button) {

    if(step == 1) {
        touchDrawManager.addPointToCurrent(ofPoint(x ,y,20 + 10 * sin(ofGetElapsedTimef() * 5)));
        
        ofLogNotice("adding line");
    }

    
}

