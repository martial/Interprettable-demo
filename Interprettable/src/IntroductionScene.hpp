//
//  IntroductionScene.hpp
//  Interprettable
//
//  Created by Martial Geoffre-Rouland on 29/10/2018.
//

#pragma once

#include "ofMain.h"
#include "AbstractScene.hpp"
#include "InteractiveButton.hpp"

class IntroductionScene : public AbstractScene{
  
public:
    
    IntroductionScene(){ };
    void setup();
    void prepass();
    
    void mousePressed(int x, int y, int button);
    void mouseReleased(int x, int y, int button);

private:
    
    virtual void onDiscoverBtnHandler(ofEventArgs & e);
    virtual void onVideoBtnHandler(ofEventArgs & e);

    
    ofImage mainImage;
    InteractiveButton discoverBtn, videoBtn;
    
};

