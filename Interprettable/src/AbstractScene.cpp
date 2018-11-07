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
    
    bDrawNextArrow = false;
}

void AbstractScene::init() {
    
    startingTimeMillis = ofGetElapsedTimeMillis();
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
    
    elapsedTimeMillis = startingTimeMillis - ofGetElapsedTimeMillis();
    
    circleRadiusPct.update(1.0 / 60.0f);
    
    mask.beginMask();
    ofSetColor(255, 255);    // more black, more transparent
    ofDrawEllipse(ofGetWidth() * .5, ofGetHeight() * .5,
                  (ofGetWidth() + ofGetHeight()) * circleRadiusPct.val(),
                  (ofGetWidth() + ofGetHeight()) * circleRadiusPct.val());
    mask.endMask();
    
}

void AbstractScene::draw() {
    
    if (bDrawNextArrow) {
        
        nextArrow.x = ofGetWidth() - nextArrow.getWidth();
        nextArrow.y = ofGetHeight() * .5 - nextArrow.getWidth() *.5;
        nextArrow.draw();
        
    }
    
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

void AbstractScene::showNextArrow() {
    
    bDrawNextArrow = true;
    nextArrow.setup();
    nextArrow.setImageUrl("assets/images/next_arrow.png");
    ofAddListener(nextArrow.clickEvent, this, &AbstractScene::onNextArrowClickHandler);
    
}

void AbstractScene::mouseReleased(int x, int y, int button) {

    if(bDrawNextArrow)
        nextArrow.mouseReleased(x, y, button);
    
    ofLogNotice("mouse released");
    
};


void AbstractScene::hideNextArrow() {
    
    bDrawNextArrow = false;
    ofRemoveListener(nextArrow.clickEvent, this, &AbstractScene::onNextArrowClickHandler);

}

void AbstractScene::onNextArrowClickHandler(ofEventArgs & e) {
    
    // default case
    mom->nextScene();
    
}


