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


typedef shared_ptr<AbstractScene> AbstractScenePtr;
class SceneManager {
  
public:
    
    void setup();
    void update();
    void draw();
    
    void setSceneIndex(int index);
    void nextScene();
    
    void startScene();
    void quitScene();
    void onQuitSceneFinishedHandler(ofEventArgs & e);
    
    vector<AbstractScenePtr > scenes;
    
    void keyPressed(int key);
    void keyReleased(int key);
    void mouseMoved(int x, int y );
    void mouseDragged(int x, int y, int button);
    void mousePressed(int x, int y, int button);
    void mouseReleased(int x, int y, int button);

    
private:
    
    int currentSceneIndex, dyingSceneIndex;
    
};

#endif /* SceneManager_hpp */
