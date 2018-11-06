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
    
    mainImage.load("scenes/introduction/barcelone-V2-01.jpg");
    
    discoverBtn.setup();
    discoverBtn.setImageUrl("assets/images/dicover_btn.png");
    videoBtn.setup();
    videoBtn.setImageUrl("assets/images/video_btn.png");
    
    showNextArrow();

}

void IntroductionScene::prepass() {
    
    ofRectangle r = ofxImgSizeUtils::getCenteredRect(ofGetWidth(), ofGetHeight(), mainImage.getWidth(), mainImage.getHeight(), true);
    
    mask.begin();
    mainImage.draw(r);
    AbstractScene::draw();
    
    discoverBtn.x = ofGetWidth() * .5 - discoverBtn.width - 20;
    videoBtn.x = ofGetWidth() * .5 + videoBtn.width - 20;

    discoverBtn.y = ofGetHeight() - discoverBtn.height - 5;
    videoBtn.y = ofGetHeight() - videoBtn.height - 5;

    
    videoBtn.draw();
    discoverBtn.draw();
    
    mask.end();
    
    mask.draw();
    
}

void IntroductionScene::mousePressed(int x, int y, int button) {
    
    //mom->nextScene();
    
}

void IntroductionScene::mouseReleased(int x, int y, int button) {
    AbstractScene::mouseReleased(x, y, button);
}

void IntroductionScene::onDiscoverBtnHandler(ofEventArgs & e) {
    
}

void IntroductionScene::onVideoBtnHandler(ofEventArgs & e) {
    
}

