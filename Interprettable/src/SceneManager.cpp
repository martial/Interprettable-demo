//
//  SceneManager.cpp
//  Interprettable
//
//  Created by Martial Geoffre-Rouland on 29/10/2018.
//

#include "SceneManager.hpp"
#include "IntroductionScene.hpp"
#include "DescriptionScene.hpp"
#include "TranslationScene.hpp"
#include "RecognitionScene.hpp"
#include "EndingScene.hpp"
#include "VideoScene.hpp"

void SceneManager::setup() {
    
    
    fonts.setup(false);
    fonts.addFont("CALVERTMTSTD", "assets/fonts/CALVERTMTSTD.ttf");
    fonts.addFont("IBMPlexSans-Light", "assets/fonts/IBMPlexSans-Light.tff");
    fonts.addFont("IBMPlexSans-Medium", "assets/fonts/IBMPlexSans-Medium.ttf");
    fonts.addFont("IBMPlexSans-Regular", "assets/fonts/IBMPlexSans-Regular.ttf");
    fonts.addFont("IBMPlexSans-Regular", "assets/fonts/IBMPlexSans-Regular.ttf");
    fonts.addFont("Amaranth-Regular", "assets/fonts/Amaranth-Regular.ttf");
    fonts.addFont("Amaranth-Bold", "assets/fonts/Amaranth-Bold.ttf");
    
    scenes.push_back(AbstractScenePtr(new IntroductionScene()));
    scenes.push_back(AbstractScenePtr(new DescriptionScene()));
    scenes.push_back(AbstractScenePtr(new TranslationScene()));
    scenes.push_back(AbstractScenePtr(new RecognitionScene()));
    scenes.push_back(AbstractScenePtr(new EndingScene()));
    scenes.push_back(AbstractScenePtr(new VideoScene()));


    for (auto & scene : scenes ) {
        scene->setMom(this);
        scene->setup();
        
    }
    
    dyingSceneIndex     = - 1;
    currentSceneIndex   = -1;
    setSceneIndex(0);
}

void SceneManager::update() {
    
    idleElapsed = ofGetElapsedTimeMillis() - startingIdleTime;
    
    if(idleElapsed > 180000 && currentSceneIndex != scenes.size() - 1 ) {
        setSceneIndex(scenes.size() - 1);
    }
    
    
    if(dyingSceneIndex >= 0)
        scenes[dyingSceneIndex]->update();
    
    scenes[currentSceneIndex]->update();

}
void SceneManager::draw() {
    
    if(dyingSceneIndex >= 0)
        scenes[dyingSceneIndex]->prepass();
    
    scenes[currentSceneIndex]->prepass();
    
}

void SceneManager::setSceneIndex(int index) {
    
    dyingSceneIndex     = currentSceneIndex;
    currentSceneIndex   = index;
    
     if(dyingSceneIndex >= 0)
         scenes[dyingSceneIndex]->quit();
    
    scenes[currentSceneIndex]->init();
    
}

void SceneManager::nextScene() {
    
    int actual = currentSceneIndex;
    actual++;
    
    // last video scene is NOT into the loop
    if(actual > scenes.size() - 2)
        actual = 0.0;
    
    setSceneIndex(actual);
}


void SceneManager::startScene() {
    
}

void SceneManager::quitScene() {
    
}

void SceneManager::onQuitSceneFinishedHandler(ofEventArgs & e) {
    
}

//------------------------------------------------------------------------

void SceneManager::keyPressed(int key) {
    
    scenes[currentSceneIndex]->keyPressed(key);
}

void SceneManager::keyReleased(int key) {
   
    scenes[currentSceneIndex]->keyReleased(key);
}

void SceneManager::mouseMoved(int x, int y ) {
    
    scenes[currentSceneIndex]->mouseMoved(x, y);
}

void SceneManager::mouseDragged(int x, int y, int button) {
    
    scenes[currentSceneIndex]->mouseDragged(x, y, button);
}

void SceneManager::mousePressed(int x, int y, int button) {
    
    startingIdleTime = ofGetElapsedTimeMillis();

    scenes[currentSceneIndex]->mousePressed(x, y, button);
}

void SceneManager::mouseReleased(int x, int y, int button) {
    
    scenes[currentSceneIndex]->mouseReleased(x, y, button);
}
