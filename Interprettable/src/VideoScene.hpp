//
//  VideoScene.hpp
//  Interprettable
//
//  Created by Martial Geoffre-Rouland on 07/11/2018.
//

#pragma once

#include "ofMain.h"
#include "AbstractScene.hpp"

class VideoScene : public AbstractScene{
    
public:
    
    VideoScene(){ };
    void init();
    void setup();
    void prepass();
    
    void mousePressed(int x, int y, int button);
    
private:
    
    ofVideoPlayer video;
};

