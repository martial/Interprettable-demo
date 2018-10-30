//
//  AbstractScene.cpp
//  Interprettable
//
//  Created by Martial Geoffre-Rouland on 29/10/2018.
//

#include "AbstractScene.hpp"
#include "SceneManager.hpp"

AbstractScene::AbstractScene() {
    
    step = 0;
    
    mask.allocate(ofGetWidth(), ofGetHeight(), ofxMask::LUMINANCE);
    
    circleRadiusPct.reset(0.0);
    circleRadiusPct.setCurve(EASE_IN);
    circleRadiusPct.setDuration(.55);
}

void AbstractScene::init() {
    
    circleRadiusPct.animateTo(1.0);
    
}

void AbstractScene::quit() {
    
    ofAddListener(circleRadiusPct.animFinished, this, &AbstractScene::onCircleRadiusQuitFinished);
    circleRadiusPct.animateTo(0.0);
    
}

void AbstractScene::onCircleRadiusQuitFinished(ofxAnimatable::AnimationEvent & e) {
    
    ofRemoveListener(circleRadiusPct.animFinished, this, &AbstractScene::onCircleRadiusQuitFinished);
    ofEventArgs dummy;
    ofNotifyEvent(quitFinishedEvent, dummy, this);
    
}


void AbstractScene::update() {
    
    circleRadiusPct.update(1.0 / 60.0f);
    
    mask.beginMask();
    ofSetColor(255);    // more black, more transparent
    ofDrawEllipse(ofGetWidth() * .5, ofGetHeight() * .5,
                  (ofGetWidth() + ofGetHeight()) * circleRadiusPct.val(),
                  (ofGetWidth() + ofGetHeight()) * circleRadiusPct.val());
    mask.endMask();
    
}

void  AbstractScene::setIntroductionImage(string url) {
    
    introductionImage.load(url);
    
}


AbstractScene::~AbstractScene() {
    
    //delete app;
    //app = NULL;
}

void AbstractScene::setMom(SceneManager * mom) {
    
    this->mom = mom;
    
}

