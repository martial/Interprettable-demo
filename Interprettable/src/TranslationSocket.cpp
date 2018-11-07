//
//  TranslationSocket.cpp
//  Interprettable
//
//  Created by Martial Geoffre-Rouland on 29/10/2018.
//

#include "TranslationSocket.hpp"

void TranslationSocket::setup() {
    
    bVerbose = false;
    
#ifndef __linux__
    addFakeContent();
#endif
    
    ofxLibwebsockets::ServerOptions options = ofxLibwebsockets::defaultServerOptions();
    options.port = 9092;
    options.bUseSSL = false; // you'll have to manually accept this self-signed cert if 'true'!
    options.documentRoot = ofToDataPath("../../../translator");
    bSetup = server.setup( options );
    server.addListener(this);
    
    // launch browser if needed
    string url = "http";
    if ( server.usingSSL() ){
        url += "s";
    }
    url += "://localhost:" + ofToString( server.getPort() );
    ofLaunchBrowser(url);
    
}

void TranslationSocket::addFakeContent() {
    
    for(int i=0; i<10; i++) {
        
        translated t;
        t.trans = "This is a super translation I love it ouh yeah";
        t.raw = "Et la on est supposés mettre du texte original mais bon ca nous donne une idée deja";

        translations.push_back(t);
        
    }
    
}


//--------------------------------------------------------------
void TranslationSocket::onConnect( ofxLibwebsockets::Event& args ){
    if(bVerbose)
        cout<<"on connected"<<endl;
}

//--------------------------------------------------------------
void TranslationSocket::onOpen( ofxLibwebsockets::Event& args ){
    if(bVerbose)
        cout<<"new connection open"<<endl;
    //sendScenariosToSocket();
    // messages.push_back("New connection from " + args.conn.getClientIP() + ", " + args.conn.getClientName() );
}

//--------------------------------------------------------------
void TranslationSocket::onClose( ofxLibwebsockets::Event& args ){
    if(bVerbose)
        cout<<"on close"<<endl;
    //messages.push_back("Connection closed");
}

//--------------------------------------------------------------
void TranslationSocket::onIdle( ofxLibwebsockets::Event& args ){
    if(bVerbose)
        cout<<"on idle"<<endl;
}

//--------------------------------------------------------------
void TranslationSocket::onMessage( ofxLibwebsockets::Event& args ){
    
    parseTranslation(args);
    
}


void TranslationSocket::parseTranslation( ofxLibwebsockets::Event& args) {
    
    // trace out string messages or JSON messages!
    if ( !args.json.isNull() ){
        messages.push_back(args.json.toStyledString()  );
    } else {
        messages.push_back( args.message );
    }
    
    // split result
    vector<string> splitted = ofSplitString(args.message, "|");
    string id       = splitted[0];
    string type     = splitted[1];
    string mesg     = splitted[2];
    
    
    // check if already exist
    translated  * trans = getTranslatedForID(id);
    

    
    if(trans) {
        
        // update
        trans->uniqueID = id;
        if(type == "RAW")
            trans->raw = mesg;
        if(type == "TRANS")
            trans->trans = mesg;
        
    } else {
        
        // create & store
        translated trans;
        trans.uniqueID = id;
        if(type == "RAW")
            trans.raw = mesg;
        if(type == "TRANS")
            trans.trans = mesg;
        
        translations.push_back(trans);
    }
    
    // if type is not a translation we send for translation
    //if(type == "RAW")
    // send back for traduction
    
    //ofLogNotice("send back to server") << args.message;
    server.send( args.message );
    
    
    // is that necessary?
    args.conn.send( args.message );
    
}

void TranslationSocket::changeOutputLang(string lang) {
    
    string message = "0|OUTPUT|"+lang;
    server.send( message );
    
}


translated * TranslationSocket::getTranslatedForID(string uniqueID) {
    
    for( int i=0; i<translations.size(); i++) {
        
        if(uniqueID == translations[i].uniqueID)
            return &translations[i];
        
    }
    
    return NULL;
}
