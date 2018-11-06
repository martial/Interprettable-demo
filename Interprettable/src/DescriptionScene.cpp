//
//  DescriptionScene.cpp
//  Interprettable
//
//  Created by Martial Geoffre-Rouland on 29/10/2018.
//

#include "DescriptionScene.hpp"
#include "ofxImgSizeUtils.h"
#include "SceneManager.hpp"

void DescriptionScene::setup() {
    
    ofFile file("scenes/presentation/config.json");
    
    if(file.exists()){
        
        file >> configJson;
    
        for(int i=0; i< configJson["images"].size(); i++) {
            
            string filename         = configJson["images"][i]["filename"];
            string title            = configJson["images"][i]["title"];
            string description      = configJson["images"][i]["text"];
            
            ofImage img;
            img.load("scenes/presentation/"+filename);
            images.push_back(img);
            
        }
        
    }
    
    currentImage = 0;
}

void DescriptionScene::init() {
    
    AbstractScene::init();
    currentImage = 0;

}


void DescriptionScene::prepass() {
    
    
    ofRectangle r = ofxImgSizeUtils::getCenteredRect(
                     ofGetWidth(), ofGetHeight(), images[currentImage].getWidth(), images[currentImage].getHeight(), false);
    
    mask.begin();
    images[currentImage].draw(r);
    
    
    ofxFontStash2::Style style;
    style.fontID = "Amaranth-Regular";
    style.fontSize = 28;
    style.color = ofColor(0,0,0);

    int boxColorR = configJson["images"][currentImage]["boxColor"]["r"];
    int boxColorG = configJson["images"][currentImage]["boxColor"]["g"];
    int boxColorB = configJson["images"][currentImage]["boxColor"]["b"];
    int boxColorA = configJson["images"][currentImage]["boxColor"]["a"];
    
    string text = configJson["images"][currentImage]["text"];
    
    float colW = 300;
    float x = 250;
    float y = 160;
    ofRectangle bbox = mom->fonts.getTextBoundsNVG(text, style, x, y, colW, OF_ALIGN_HORZ_LEFT);
   
    float padding = 15;
    bbox.width += padding *2;
    bbox.height += padding * 2;
    bbox.x -= padding;
    bbox.y -= padding;

    ofSetColor(boxColorR,boxColorG,boxColorB,boxColorA);
    ofDrawRectangle(bbox);
    
    ofSetColor(0,255);
    mom->fonts.drawColumn(text, style, x, y, colW);
   
    
    
    mask.end();
    
    mask.draw();
    
}

void DescriptionScene::mousePressed(int x, int y, int button) {
    
    currentImage++;
    if(currentImage >= configJson["images"].size() ) {
        currentImage = configJson["images"].size() - 1;
        mom->nextScene();
    }
    
}





