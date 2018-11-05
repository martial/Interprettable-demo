//
//  TranslationScene.cpp
//  Interprettable
//
//  Created by Martial Geoffre-Rouland on 30/10/2018.
//

#include "TranslationScene.hpp"
#include "ofxImgSizeUtils.h"
#include "SceneManager.hpp"
#include "ofApp.h"

void TranslationScene::setup() {
    
    setIntroductionImage("scenes/translation/barcelone-V2-8.png");
    backgroundImage.load("scenes/translation/background.jpg");
    
    translationMask = new ofxMask();
    translationMask->allocate(ofGetWidth(), ofGetHeight(), ofxMask::LUMINANCE);
    maskImage.load("scenes/translation/mask.jpg");
    
    
    translationMask->beginMask();
    ofSetColor(255);
    maskImage.draw(0.0,0.0);
    translationMask->endMask();
   
    
}

void TranslationScene::init() {

    AbstractScene::init();
    step = 0;
    
}


void TranslationScene::prepass() {
    
    
    ofRectangle r;
    
    mask.begin();
    
    if (step == 0 ) {
        
        r = ofxImgSizeUtils::getCenteredRect(ofGetWidth(), ofGetHeight(), introductionImage.getWidth(), introductionImage.getHeight(), true);
        introductionImage.draw(r);
    }
   
    if (step == 1 ) {
      
        r = ofxImgSizeUtils::getCenteredRect(ofGetWidth(), ofGetHeight(), backgroundImage.getWidth(), backgroundImage.getHeight(), true);
        backgroundImage.draw(r);
        

        translationMask->begin();
        
        // draw all text
       
        
        ofxFontStash2::Style styleLabel;
        styleLabel.fontID = "Amaranth-Regular";
        styleLabel.fontSize = 22;
        styleLabel.color = ofColor(255,0,0);
        
        ofxFontStash2::Style styleLabelTranslation;
        styleLabelTranslation.fontID = "Amaranth-Regular";
        styleLabelTranslation.fontSize = 22;
        styleLabelTranslation.color = ofColor(0,0,0);

        ofApp * app = (ofApp*)ofGetAppPtr();
        
        float yPos = 400;


        for(int i=0; i<app->translationSocket.translations.size(); i++) {
            
            ofPushMatrix();
            ofTranslate(250, yPos);
                        
            string text = app->translationSocket.translations[i].raw;
            float colW = 450;
            float x = 0.0;
            float y = 0.0;
            ofSetColor(255,255);
            ofRectangle bbox = mom->fonts.drawColumn(text, styleLabel, x, y, colW);

       translationSocket.translations[i].trans;
            x = 0.0;
            y = bbox.getHeight() + 20;
            ofSetColor(255,255);
            bbox = mom->fonts.drawColumn(text, styleLabelTranslation, x, y, colW);

            
            yPos += bbox.y + bbox.getHeight() + 40;

            
            ofPopMatrix();

            
            
        }
        
        translationMask->end();
        
        translationMask->draw();

        
        
    }
    
    
    
    mask.end();
    
    
    mask.draw();
    
}

void TranslationScene::mousePressed(int x, int y, int button) {
    
    step++;
    
}

