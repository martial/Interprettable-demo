#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofBackground(255,255,255);

}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){
    
    ofSetColor(0,0,0);
    touchDrawManager.draw();
    
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    
    if( key == ' ')
        touchDrawManager.clear();
    
    if( key == 's')
        touchDrawManager.saveToImage();
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){
    
    touchDrawManager.addPointToCurrent(ofPoint(x ,y,20 + 10 * sin(ofGetElapsedTimef() * 5)));

}
  

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
    touchDrawManager.addLine();
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

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

