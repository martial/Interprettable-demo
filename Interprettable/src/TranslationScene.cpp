//
//  TranslationScene.cpp
//  Interprettable
//
//  Created by Martial Geoffre-Rouland on 30/10/2018.
//

#include "TranslationScene.hpp"
#include "ofxImgSizeUtils.h"
#include "SceneManager.hpp"
#include "ofApp.h"

void TranslationScene::setup() {
    
    setIntroductionImage("scenes/translation/barcelone-V2-8.png");
    backgroundImage.load("scenes/translation/background.jpg");
    
    translationMask = new ofxMask();
    translationMask->allocate(ofGetWidth(), ofGetHeight(), ofxMask::LUMINANCE);
    maskImage.load("scenes/translation/mask.jpg");
    
    translationMask->beginMask();
    ofSetColor(255);
    maskImage.draw(0.0,0.0);
    translationMask->endMask();
    
    
    box2d.init();
    box2d.setGravity(0, 0.01);
    box2d.createBounds();
    box2d.setFPS(60.0);
    box2d.registerGrabbing();
   
    font.load("assets/fonts/Amaranth-Regular.ttf", 32);
   
    
    ofFile file("scenes/translation/languages.json");
    file >> languagesJson;
    
    for(int i=0; i<languagesJson.size(); i++) {
        
        string label = languagesJson[i][0];
        ofRectangle bbox = font.getStringBoundingBox(label, 0, 0);
        
        boxes.push_back(shared_ptr<ofxBox2dRect>(new ofxBox2dRect));
        boxes.back().get()->setPhysics(0.7, 0.83, 0.5);
        boxes.back().get()->setup(box2d.getWorld(), 1000, 500, bbox.width, bbox.height);
        
    }
    
    colorImg.allocate(maskImage.getWidth(), maskImage.getHeight());
    grayImage.allocate(maskImage.getWidth(), maskImage.getHeight());

    
    colorImg.setFromPixels(maskImage.getPixels());
    grayImage = colorImg;
    grayImage.threshold(80);
    contourFinder.findContours(grayImage, 20, (maskImage.getWidth()* maskImage.getHeight())/3, 10, false);    // find holes
    
    for(int i=0; i<contourFinder.blobs.size(); i++ ) {
        
        ofPolyline p;
        for(int j=0; j<contourFinder.blobs[i].pts.size(); j++) {
            
            float x = contourFinder.blobs[i].pts[j].x;
            float y = contourFinder.blobs[i].pts[j].y;
            
            p.addVertex(x,y);
            
        }
        
        p.simplify();
        p.close();
        
        auto poly = std::make_shared<ofxBox2dPolygon>();
        poly->addVertices(p.getVertices());
        poly->setClosed(true);
        poly->setPhysics(0.0, 0.0, 0.0);
        poly->enableGravity(false);
        
        poly->triangulatePoly();
        poly->create(box2d.getWorld());
        polyShapes.push_back(poly);
        
    }
    
   


}

void TranslationScene::init() {

    AbstractScene::init();
    step = 0;
    hideNextArrow();
    currentLanguage = 0;
    
    for(int i=0; i<boxes.size(); i++) {

        boxes[i].get()->setPosition(1200 + ofRandom(200), 200);
        
    }
}


void TranslationScene::prepass() {
    
    box2d.update();

    
    ofRectangle r;
    
    mask.begin();
    
    if (step == 0 ) {
        
        r = ofxImgSizeUtils::getCenteredRect(ofGetWidth(), ofGetHeight(), introductionImage.getWidth(), introductionImage.getHeight(), true);
        introductionImage.draw(r);
    }
   
    if (step == 1 ) {
      
        r = ofxImgSizeUtils::getCenteredRect(ofGetWidth(), ofGetHeight(), backgroundImage.getWidth(), backgroundImage.getHeight(), true);
        backgroundImage.draw(r);
        

        translationMask->begin();
        
        // draw all text
        
        ofxFontStash2::Style styleLabel;
        styleLabel.fontID = "Amaranth-Regular";
        styleLabel.fontSize = 22;
        styleLabel.color = ofColor(255,0,0);
        
        ofxFontStash2::Style styleLabelTranslation;
        styleLabelTranslation.fontID = "Amaranth-Regular";
        styleLabelTranslation.fontSize = 22;
        styleLabelTranslation.color = ofColor(0,0,0);

        ofApp * app = (ofApp*)ofGetAppPtr();
        
        float yPos = 400;


        for(int i=app->translationSocket.translations.size() - 1; i>=0; i--) {
            
            ofPushMatrix();
            ofTranslate(250, yPos);
                        
            string text = app->translationSocket.translations[i].raw;
            float colW = 450;
            float x = 0.0;
            float y = 0.0;
            ofSetColor(255,255);
            ofRectangle bbox = mom->fonts.drawColumn(text, styleLabel, x, y, colW);

            text = app->translationSocket.translations[i].trans;
            x = 0.0;
            y = bbox.getHeight() + 20;
            ofSetColor(255,255);
            bbox = mom->fonts.drawColumn(text, styleLabelTranslation, x, y, colW);

            yPos += bbox.y + bbox.getHeight() + 40;

            ofPopMatrix();
            
        }
        
        translationMask->end();
        
        translationMask->draw();
        
        
        // draw translations
        for(int i=0; i<boxes.size(); i++) {
            
            ofFill();
            
            string label = languagesJson[i][0];
            
            ofRectangle bbox = font.getStringBoundingBox(label, 0, 0);
            
            ofPushMatrix();
            ofTranslate(boxes[i].get()->getPosition().x, boxes[i].get()->getPosition().y);
            ofRotateDeg(boxes[i].get()->getRotation());
            
            float padding = 5;
            ofRectangle backBox = bbox;
            backBox.x -= padding + bbox.width * .5;
            backBox.y -= padding - bbox.height * .5;
            backBox.width += padding * 2;
            backBox.height += padding * 2;
            
            if( i != currentLanguage)
                ofSetColor(20,120,120);
            else
                ofSetColor(255,0,0);
            
            ofDrawRectRounded(backBox, 5, 5, 5, 5);
            
            ofSetColor(255);
            font.drawString(label, - bbox.width * .5, + bbox.height * .5);
            
            ofPopMatrix();

        }
        
        
    }
    
    
    ofSetColor(255, 255);

    AbstractScene::draw();
    
    
    mask.end();
    mask.draw();
    
}

void TranslationScene::mousePressed(int x, int y, int button) {
    
    if(step == 0) {
        step++;
        showNextArrow();
    }
    
    
    // oh man some math fun
    currentLanguage = 0;
    for(int i=0; i<boxes.size(); i++) {
        
        ofMatrix4x4 matrix;
        
        matrix.glTranslate( boxes[i].get()->getPosition().x, boxes[i].get()->getPosition().y, 0 );
        matrix.glRotate( boxes[i].get()->getRotation(), 0, 0, 1 );
        matrix.glScale( 1, 1, 1 );
        
        ofVec3f mouse( x, y, 0 );
        mouse = mouse * matrix.getInverse();
        
        string label = languagesJson[i][0];
        ofRectangle bbox = font.getStringBoundingBox(label, 0, 0);
        bbox.x -= + bbox.width * .5;
        bbox.y -= - bbox.height * .5;
        bool isInside = bbox.inside( mouse );
        if(isInside) {
            currentLanguage = i;
            
            string output = languagesJson[i][1][0];
            ofApp * app = (ofApp*)ofGetAppPtr();
            app->translationSocket.changeOutputLang(output);
        }
    }
    
   
    
}

