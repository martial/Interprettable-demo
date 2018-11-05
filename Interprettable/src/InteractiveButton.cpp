//
//  InteractiveButton.cpp
//  Interprettable
//
//  Created by Martial Geoffre-Rouland on 05/11/2018.
//

#include "InteractiveButton.hpp"


void InteractiveButton::setup() {
    
    bActive = false;
    
}

void InteractiveButton::setImageUrl(string url) {
    
    img.load(url);
    setWidth(img.getWidth());
    setHeight(img.getHeight());
    
}


void InteractiveButton::draw() {
    
    if (img.isAllocated()) {
        img.draw(x, y);
    }
    
}

void InteractiveButton::mousePressed(int x, int y, int button) {
    
   
    
    
}

void InteractiveButton::mouseReleased(int x, int y, int button ) {
    
    bActive = false;

    
    ofLogNotice("inside button") << x << " " << y;
    
    if( inside(x,y) ) {
        bActive = true;
        ofEventArgs e;
        ofNotifyEvent(clickEvent, e);
    }
    
}
