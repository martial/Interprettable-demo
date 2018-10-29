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





