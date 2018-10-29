//
//  TouchDrawManager.cpp
//  TouchDrawTest
//
//  Created by Martial Geoffre-Rouland on 29/10/2018.
//

#include "TouchDrawManager.hpp"

void TouchDrawManager::setup() {
    
    fbo.allocate(ofGetWidth(), ofGetHeight(), GL_RGB);
    fbo.begin();
    ofClear(255,255,255, 0);
    fbo.end();

}

void TouchDrawManager::update() {
    
}

void TouchDrawManager::draw() {
    
    fbo.begin();
    ofBackground(255);
    ofSetColor(0);
    for (int i=0; i<lines.size(); i++) {
        drawPolyineThickWZ(lines[i]);
    }
    fbo.end();
  
    
}

void TouchDrawManager::clear(){
    
    lines.clear();
    
}

void TouchDrawManager::addLine() {
    
    ofPolyline * line = new ofPolyline();
    lines.push_back(line);
    currentLineId = lines.size() - 1;
    
}

void TouchDrawManager::addPointToCurrent(ofPoint pnt) {
    
    lines[currentLineId]->addVertex(pnt);

}


void TouchDrawManager::drawPolyineThickWZ( ofPolyline * line){
    
    ofMesh meshy;
    meshy.setMode(OF_PRIMITIVE_TRIANGLE_STRIP);
    
    float widthSmooth = 10;
    float angleSmooth;
    
    for (int i = 0;  i < line->getVertices().size(); i++){
        int me_m_one = i-1;
        int me_p_one = i+1;
        if (me_m_one < 0) me_m_one = 0;
        if (me_p_one ==  line->getVertices().size()) me_p_one =  line->getVertices().size()-1;
        ofPoint diff = line->getVertices()[me_p_one] - line->getVertices()[me_m_one];
        float angle = atan2(diff.y, diff.x);
        float dist = diff.length();
        ofPoint offset;
        offset.x = cos(angle + PI/2) * line->getVertices()[i].z;
        offset.y = sin(angle + PI/2) * line->getVertices()[i].z;
        meshy.addVertex(  line->getVertices()[i] +  offset );
        meshy.addVertex(  line->getVertices()[i] -  offset );
    }
    
    meshy.draw();
    
    
    
}
void TouchDrawManager::drawPolyineThick( ofPolyline * line, int thickness){
    
    
    ofMesh meshy;
    meshy.setMode(OF_PRIMITIVE_TRIANGLE_STRIP);
    
    float widthSmooth = 10;
    float angleSmooth;
    
    for (int i = 0;  i < line->getVertices().size(); i++){
        int me_m_one = i-1;
        int me_p_one = i+1;
        if (me_m_one < 0) me_m_one = 0;
        if (me_p_one ==  line->getVertices().size()) me_p_one =  line->getVertices().size()-1;
        ofPoint diff = line->getVertices()[me_p_one] - line->getVertices()[me_m_one];
        float angle = atan2(diff.y, diff.x);
        float dist = diff.length();
        ofPoint offset;
        offset.x = cos(angle + PI/2) * thickness;
        offset.y = sin(angle + PI/2) * thickness;
        meshy.addVertex(  line->getVertices()[i] +  offset );
        meshy.addVertex(  line->getVertices()[i] -  offset );
    }
    
    meshy.draw();
    
    
}

void TouchDrawManager::saveToImage() {
    
    fbo.readToPixels(pixels);
    pixels.setImageType(OF_IMAGE_COLOR);
    ofSaveImage(pixels, "ouput.jpg");

    
}
