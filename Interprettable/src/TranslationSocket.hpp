//
//  TranslationSocket.hpp
//  Interprettable
//
//  Created by Martial Geoffre-Rouland on 29/10/2018.
//

#ifndef TranslationSocket_hpp
#define TranslationSocket_hpp

#include "ofMain.h"
#include "ofxLibwebsockets.h"

#define NUM_MESSAGES 2

struct translated {
    
    string uniqueID;
    string raw, trans;
    
    
};

class TranslationSocket {
  
public:
    
    void setup();
    
    void addFakeContent();

    
    void onConnect( ofxLibwebsockets::Event& args );
    void onOpen( ofxLibwebsockets::Event& args );
    void onClose( ofxLibwebsockets::Event& args );
    void onIdle( ofxLibwebsockets::Event& args );
    void onMessage( ofxLibwebsockets::Event& args );
    void onBroadcast( ofxLibwebsockets::Event& args );
    
    void parseTranslation( ofxLibwebsockets::Event& args);
    translated * getTranslatedForID(string uniqueID);

    vector<translated> translations;

    void changeOutputLang(string lang);
    
private:
    
    // sockets
    ofxLibwebsockets::Server server;
    bool bSetup;
    vector<string> messages;
    int translationFontSize;
    
    bool bVerbose;
};

#endif /* TranslationSocket_hpp */
