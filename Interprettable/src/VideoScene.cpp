//
//  VideoScene.cpp
//  Interprettable
//
//  Created by Martial Geoffre-Rouland on 07/11/2018.
//

#include "VideoScene.hpp"
#include "ofxImgSizeUtils.h"
#include "SceneManager.hpp"

void VideoScene::setup() {
    
    video.load("assets/videos/Interpré-tabble.mp4");
    
}

void VideoScene::init() {
    
    AbstractScene::init();
    video.play();
    video.setPosition(0.0);
    
}


void VideoScene::prepass() {
    
    video.update();
    
    ofRectangle r = ofxImgSizeUtils::getCenteredRect(ofGetWidth(), ofGetHeight(), video.getWidth(), video.getHeight(), true);
    
    mask.begin();
    video.draw(r);
    mask.end();
    
    mask.draw();

}

void VideoScene::mousePressed(int x, int y, int button) {
    
    video.stop();
    mom->nextScene();
    
}

