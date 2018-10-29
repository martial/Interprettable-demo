//
//  IntroductionScene.hpp
//  Interprettable
//
//  Created by Martial Geoffre-Rouland on 29/10/2018.
//

#pragma once

#include "ofMain.h"
#include "AbstractScene.hpp"

class IntroductionScene : public AbstractScene{
  
public:
    
    IntroductionScene(){ };
    void setup();
    void prepass();
    
    void mousePressed(int x, int y, int button);

private:
    
    ofImage mainImage;
    
};

