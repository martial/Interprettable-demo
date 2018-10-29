//
//  AbstractScene.hpp
//  Interprettable
//
//  Created by Martial Geoffre-Rouland on 29/10/2018.
//

#ifndef AbstractScene_hpp
#define AbstractScene_hpp

#include "ofMain.h"
#include "ofxMask.h"
#include "ofxAnimatableFloat.h"

class SceneManager;

class AbstractScene {
    
public:
    
    AbstractScene();
    ~AbstractScene();
    
    virtual void setup(){};
    virtual void update();
    virtual void prepass(){};
    virtual void draw(){};
    
    virtual void init();
    virtual void quit();
    
    virtual void updateMask(){};
    
    virtual void setMom(SceneManager * mom);
    
    ofEvent<ofEventArgs>    quitFinishedEvent;
    
    virtual void keyPressed(int key){};
    virtual void keyReleased(int key){};
    virtual void mouseMoved(int x, int y ){};
    virtual void mouseDragged(int x, int y, int button){};
    virtual void mousePressed(int x, int y, int button){};
    virtual void mouseReleased(int x, int y, int button){};
    
protected:
    
    SceneManager * mom;
    ofxAnimatableFloat      circleRadiusPct;
    ofxMask                 mask;
    
private:
    
    void onCircleRadiusQuitFinished(ofxAnimatable::AnimationEvent & e);
};

#endif /* AbstractScene_hpp */
