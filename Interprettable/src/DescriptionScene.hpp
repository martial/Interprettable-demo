//
//  DescriptionScene.hpp
//  Interprettable
//
//  Created by Martial Geoffre-Rouland on 29/10/2018.
//

#pragma once

#include "ofMain.h"
#include "AbstractScene.hpp"

class DescriptionScene : public AbstractScene{
    
public:
    
    DescriptionScene(){ };
    void setup();
    void prepass();
    
    void init();

    void mousePressed(int x, int y, int button);
    void onNextArrowClickHandler(ofEventArgs & e);

    
private:
    
    ofJson configJson;
    vector<ofImage> images;
    int currentImage;
};

