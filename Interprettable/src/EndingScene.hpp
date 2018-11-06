//
//  EndingScene.hpp
//  Interprettable
//
//  Created by Martial Geoffre-Rouland on 05/11/2018.
//

#pragma once

#include "ofMain.h"
#include "AbstractScene.hpp"

class EndingScene : public AbstractScene{
    
public:
    
    EndingScene(){ };
    void setup();
    void prepass();
    
    void mousePressed(int x, int y, int button);
    
private:
    
    ofImage mainImage;
};

