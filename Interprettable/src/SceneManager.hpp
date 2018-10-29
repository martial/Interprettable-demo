//
//  SceneManager.hpp
//  Interprettable
//
//  Created by Martial Geoffre-Rouland on 29/10/2018.
//

#ifndef SceneManager_hpp
#define SceneManager_hpp

#include "ofMain.h"
#include "AbstractScene.hpp"

class SceneManager {
  
public:
    
    void setup();
    void update();
    void draw();
    
    void setSceneIndex(int index);
    
    void startScene();
    void quitScene();
    void onQuitSceneFinishedHandler(ofEventArgs & e);
    
    
    
private:
    
    vector<AbstractScene* > scenes;
   
    
};

#endif /* SceneManager_hpp */
