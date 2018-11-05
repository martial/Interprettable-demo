//
//  InteractiveButton.hpp
//  Interprettable
//
//  Created by Martial Geoffre-Rouland on 05/11/2018.
//

#ifndef InteractiveButton_hpp
#define InteractiveButton_hpp

#include "ofMain.h"

class InteractiveButton : public ofRectangle {
  
public:
    
    
    void setup();
    void setImageUrl(string url);
    
    void draw();
    
    void mousePressed(int x, int y, int button);
    void mouseReleased(int x, int y, int button);
    
    bool bActive;

    ofEvent<ofEventArgs> clickEvent;
    string label;
    
private:
    
    ofImage img;
    
    
    
};

#endif /* InteractiveButton_hpp */
