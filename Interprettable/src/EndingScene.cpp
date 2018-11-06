//
//  EndingScene.cpp
//  Interprettable
//
//  Created by Martial Geoffre-Rouland on 05/11/2018.
//

#include "EndingScene.hpp"

#include "ofxImgSizeUtils.h"
#include "SceneManager.hpp"

void EndingScene::setup() {
    mainImage.load("scenes/ending/ending.png");
    
    
}

void EndingScene::prepass() {
    
    ofRectangle r = ofxImgSizeUtils::getCenteredRect(ofGetWidth(), ofGetHeight(), mainImage.getWidth(), mainImage.getHeight(), true);
    
    mask.begin();
    mainImage.draw(r);
    mask.end();
    
    mask.draw();
    
}

void EndingScene::mousePressed(int x, int y, int button) {
    
    mom->nextScene();
    
}

