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
    
    clearButton.setup();
    clearButton.setImageUrl("scenes/recognition/erase_btn.png");
    
    // caption OSC
    osc.setup(2223);
    sender.setup("localhost", 2222);
    
    ofxOscMessage mess;
    mess.setAddress("/img");
    mess.addStringArg(ofToDataPath("output.jpg", true));
    sender.sendMessage(mess, false);
    
}

void RecognitionScene::init() {
    
    AbstractScene::init();
    step = 0;
    
    touchDrawManager.clear();
    ofAddListener(clearButton.clickEvent, this, &RecognitionScene::onClearButtonClickedEventHandler);
    
    string imgPath = touchDrawManager.saveToImage();
    ofxOscMessage mess;
    mess.setAddress("/img");
    mess.addStringArg(ofToDataPath(imgPath, true));
    sender.sendMessage(mess, false);

}

void RecognitionScene::update() {
    
    AbstractScene::update();
    
    while(osc.hasWaitingMessages()){
        
        // get the next message
        ofxOscMessage m;
        osc.getNextMessage(m);
        
        //  ofLogNotice("message") << m.getAddress();
        caption = m.getAddress();
        ofLogNotice("Message received ") << caption;
        
        /*
        string imgPath = touchDrawManager.saveToImage();
        ofxOscMessage mess;
        mess.setAddress("/img");
        mess.addStringArg(ofToDataPath(imgPath, true));
        sender.sendMessage(mess, false);
        */
        
    }
    
}


void RecognitionScene::prepass() {
    
    
    ofRectangle r;
    
    mask.begin();
    
    ofSetColor(255,255);
    
    if (step == 0 ) {
        
        r = ofxImgSizeUtils::getCenteredRect(ofGetWidth(), ofGetHeight(), introductionImage.getWidth(), introductionImage.getHeight(), true);
        introductionImage.draw(r);
        
    }
    
    if (step == 1 ) {
        
        // draw background
        r = ofxImgSizeUtils::getCenteredRect(ofGetWidth(), ofGetHeight(), backgroundImage.getWidth(), backgroundImage.getHeight(), true);
        backgroundImage.draw(r);
        
        // draw drawing zone mask
        drawingMask->begin();
        touchDrawManager.draw();
        drawingMask->end();
        drawingMask->draw();
        
        // draw buttons
        clearButton.x = 580;
        clearButton.y = 255;
        clearButton.draw();
        
        // draw results text
        ofxFontStash2::Style styleLabel;
        styleLabel.fontID = "Amaranth-Regular";
        styleLabel.fontSize = 42;
        styleLabel.color = ofColor(20,125,140);
        
        string label = "I can't find anything";
        
        if( caption != "rien")
            label = "I see a " + caption + ". Is this correct ? ";
        
        if( caption == "Not sure")
            label = "I'm not sure to recognize this.";
        
        // not sure why I need to flip this ?
        ofPushMatrix();
        ofTranslate(1150, 400);
        ofRotateX(-180);
        mom->fonts.drawColumn(label, styleLabel, 0.0, 0.0, 400);

        ofPopMatrix();
        
    }
    
    mask.end();
    mask.draw();
    
}

void RecognitionScene::onClearButtonClickedEventHandler(ofEventArgs & e) {

    touchDrawManager.clear();
    
    caption = "rien";
    
    string imgPath = touchDrawManager.saveToImage();
    ofxOscMessage mess;
    mess.setAddress("/img");
    mess.addStringArg(ofToDataPath(imgPath, true));
    sender.sendMessage(mess, false);
    
}


void RecognitionScene::mousePressed(int x, int y, int button) {
    
    if(step == 0)
        step++;
    
    if(step == 1) {
        
        touchDrawManager.addLine();
        
    }
    
}

void RecognitionScene::mouseDragged(int x, int y, int button) {

    if(step == 1) {
        
        touchDrawManager.addPointToCurrent(ofPoint(x ,y,10 + 5 * sin(ofGetElapsedTimef() * 2.5)));
        
    }
    
}

void RecognitionScene::mouseReleased(int x, int y, int button) {
    
    if(step == 1) {
        
        clearButton.mouseReleased(x,y,button);
        
        string imgPath = touchDrawManager.saveToImage();
        ofxOscMessage mess;
        mess.setAddress("/img");
        mess.addStringArg(ofToDataPath(imgPath, true));
        sender.sendMessage(mess, false);
        
    }
    
}


