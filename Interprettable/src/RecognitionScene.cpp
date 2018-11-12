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
    
    
    resultPct.setDuration(0.4);
    
    ofFile file("scenes/recognition/config.json");
    file >> configJson;
    
}

void RecognitionScene::init() {
    
    AbstractScene::init();
    step = 0;
    
    touchDrawManager.clear();
    ofAddListener(clearButton.clickEvent, this, &RecognitionScene::onClearButtonClickedEventHandler);
    
    bHasFoundDrawing = false;
    
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
        
        // do we have a change ?
        
        bool bHasFound = true;
        if (caption == "rien" || caption == "Not sure")
            bHasFound = false;
        
        if(touchDrawManager.lines.size() == 0)
            bHasFound = false;
        
        if( bHasFound != bHasFoundDrawing ) {
            // we have a change here
            loadImageResults();
            switchResults();
            bHasFoundDrawing = bHasFound;
        }
        
        
        
        
        /*
        string imgPath = touchDrawManager.saveToImage();
        ofxOscMessage mess;
        mess.setAddress("/img");
        mess.addStringArg(ofToDataPath(imgPath, true));
        sender.sendMessage(mess, false);
        */
        
    }
    
    resultPct.update(1.0 / 60.0f);
    
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
        

        drawInvitationText();
        drawResult();
        
    }
    AbstractScene::draw();
    mask.end();
    mask.draw();
    
}

void RecognitionScene::drawInvitationText() {
    
    
    float opacity = ( 1.0 - resultPct.val() ) * 255.0;
    
    if(opacity == 0.0)
        return;
    
    
    // draw invitation text
    
    ofxFontStash2::Style invitationLabel;
    invitationLabel.fontID = "Amaranth-Regular";
    invitationLabel.fontSize = 64;
    invitationLabel.color = ofColor(20,125,140, opacity);
    
    // not sure why I need to flip this ?
    ofPushMatrix();
    ofTranslate(1150, 800);
    ofRotateX(-180);
    mom->fonts.drawColumn("Don't be shy, draw a moon, a house, an arrow, an ambulance, a baby bottle, a bed! ", invitationLabel, 0.0, 0.0, 500);
    ofPopMatrix();
    
    // draw results text
    ofxFontStash2::Style styleLabel;
    styleLabel.fontID = "Amaranth-Regular";
    styleLabel.fontSize = 42;
    styleLabel.color = ofColor(20,125,140, opacity);
    
    string label = "I can't find anything";
    
    if( caption != "rien")
        label = "I see a " + caption + ". Is this correct ? ";
    
    if( caption == "Not sure")
        label = "I'm not sure to recognize this.";
    
    if(touchDrawManager.lines.size() == 0)
        label = "I'm waiting for your drawings !";
    
    // not sure why I need to flip this ?
    ofPushMatrix();
    ofTranslate(1150, 400);
    ofRotateX(-180);
    mom->fonts.drawColumn(label, styleLabel, 0.0, 0.0, 500);
    
    ofPopMatrix();
    
}

void RecognitionScene::loadImageResults() {
    
    // clean a bit
    for(int i=0; i<imagesResult.size(); i++) {
        imagesResult[i].clear();
    }
    imagesResult.clear();
    
    // load images in folders
    string path = "scenes/recognition/"+caption;
    ofDirectory dir(path);
    dir.allowExt("png");
    dir.listDir();
    
    for(int i = 0; i < dir.size(); i++){
        ofImage img;
        img.load(dir.getPath(i));
        imagesResult.push_back(img);
    }
    
}

void RecognitionScene::drawResult() {
    
    float xPos = 1150;
    float yPos = 150;
    
    float opacity = (resultPct.val() ) * 255.0;
    if(opacity == 0.0)
        return;
    
    ofEnableAlphaBlending();
    ofSetColor(255, opacity);
    
    int cnt=0;
    float width = 0.0;
    for(int i=0; i< imagesResult.size(); i++) {
     
        imagesResult[i].draw(xPos, yPos);
        yPos +=  imagesResult[i].getHeight();
                width = MAX(imagesResult[i].getWidth(), width);
        
        cnt++;

        if(cnt > 1) {
            xPos = 1150 + width +10;
            width = 0;
            yPos = 150;
            cnt = 0;
            
        }
    }
    
    string translated = caption;
    string description = "";
    
    if(caption != "rien" && caption.size() > 0) {
        
        ofJson jsonBlock = getConfigByLabel(caption);
        translated = jsonBlock["translation"];
        description = jsonBlock["description"];
        
    }

    // not sure why I need to flip this ?
    
    string label = "I can't find anything";
    if( caption != "rien")
        label = "I see a " + translated + " !";
    
    if( caption == "Not sure")
        label = "I'm not sure to recognize this.";
    
    if(touchDrawManager.lines.size() == 0)
        label = "I'm waiting for your drawings !";
    
    // draw results text
    ofxFontStash2::Style styleLabel;
    styleLabel.fontID = "Amaranth-Bold";
    styleLabel.fontSize = 64;
    styleLabel.color = ofColor(20,125,140, opacity);
    
    // draw results text
    ofxFontStash2::Style styleTinyLabel;
    styleTinyLabel.fontID = "Amaranth-Regular";
    styleTinyLabel.fontSize = 42;
    styleTinyLabel.color = ofColor(20,125,140, opacity);
    
    // not sure why I need to flip this ?
    ofPushMatrix();
    ofTranslate(1150, 500);
    ofRotateX(-180);
    mom->fonts.drawColumn(label, styleLabel, 0.0, 0.0, 500);
    
    mom->fonts.drawColumn(description, styleTinyLabel, 0.0, 80, 500);

    ofPopMatrix();
    
    
}

void RecognitionScene::switchResults() {
    
     if(bHasFoundDrawing)
         resultPct.animateTo(0.0);
    else
        resultPct.animateTo(1.0);
    
    

}

ofJson RecognitionScene::getConfigByLabel(string label) {
    
    
    
    for (int i=0; i<configJson.size(); i++) {
        
        if (configJson[i]["label"] == label)
            return (configJson[i]);
        
    }
    
    
    ofJson dummy;
    return dummy;
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
    

    
    if(step == 0) {
        step++;
        showNextArrow();
    }
    
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
    
    AbstractScene::mouseReleased(x,y,button);
    
    if(step == 1) {
        
        clearButton.mouseReleased(x,y,button);
        
        string imgPath = touchDrawManager.saveToImage();
        ofxOscMessage mess;
        mess.setAddress("/img");
        mess.addStringArg(ofToDataPath(imgPath, true));
        sender.sendMessage(mess, false);
        
    }
    
}


