#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){

    ofSetFrameRate(60);
    ofSetCircleResolution(128);
    sceneManager.setup();
    
    translationSocket.setup();
    
}

//--------------------------------------------------------------
void ofApp::update(){
    sceneManager.update();

}

//--------------------------------------------------------------
void ofApp::draw(){

    ofBackground(255);
    sceneManager.draw();
    
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

   // sceneManager.nextScene();
    
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
    sceneManager.keyReleased(key);
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){
    sceneManager.mouseMoved(x, y);

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){
    sceneManager.mouseDragged(x, y, button);

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
    sceneManager.mousePressed(x, y , button);

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){
    sceneManager.mouseReleased(x, y, button);

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
