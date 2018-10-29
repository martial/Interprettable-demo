//
//  IntroductionScene.cpp
//  Interprettable
//
//  Created by Martial Geoffre-Rouland on 29/10/2018.
//

#include "IntroductionScene.hpp"
#include "ofxImgSizeUtils.h"
#include "SceneManager.hpp"



void IntroductionScene::setup() {
    mainImage.load("scenes/introduction/barcelone-V2-01.png");
    

}

void IntroductionScene::prepass() {
    
    ofRectangle r = ofxImgSizeUtils::getCenteredRect(
                                                     ofGetWidth(), ofGetHeight(), mainImage.getWidth(), mainImage.getHeight(), true);
    
    mask.begin();
    mainImage.draw(r);
    mask.end();
    
    
    mask.draw();
    
}

void IntroductionScene::mousePressed(int x, int y, int button) {
    
    mom->nextScene();
    
}

