//
//  PresentationScene.cpp
//  Interprettable
//
//  Created by Martial Geoffre-Rouland on 29/10/2018.
//

#include "PresentationScene.hpp"

void PresentationScene::prepass() {
    
    mask.begin();
    ofSetColor(255,0,0);
    ofDrawRectangle(0.0, 0.0, ofGetWidth(), ofGetHeight());
    mask.end();
    
    
    mask.draw();
    
}
