//
//  TranslationSocket.cpp
//  Interprettable
//
//  Created by Martial Geoffre-Rouland on 29/10/2018.
//

#include "TranslationSocket.hpp"

void TranslationSocket::setup() {
    
    ofxLibwebsockets::ServerOptions options = ofxLibwebsockets::defaultServerOptions();
    options.port = 9092;
    options.bUseSSL = false; // you'll have to manually accept this self-signed cert if 'true'!
    options.documentRoot = ofToDataPath("../../../translator");
    bSetup = server.setup( options );
    server.addListener(this);
    
    string url = "http";
    if ( server.usingSSL() ){
        url += "s";
    }
    url += "://localhost:" + ofToString( server.getPort() );
    ofLaunchBrowser(url);
    
}

//--------------------------------------------------------------
void TranslationSocket::onConnect( ofxLibwebsockets::Event& args ){
    cout<<"on connected"<<endl;
}

//--------------------------------------------------------------
void TranslationSocket::onOpen( ofxLibwebsockets::Event& args ){
    cout<<"new connection open"<<endl;
    //sendScenariosToSocket();
    // messages.push_back("New connection from " + args.conn.getClientIP() + ", " + args.conn.getClientName() );
}

//--------------------------------------------------------------
void TranslationSocket::onClose( ofxLibwebsockets::Event& args ){
    cout<<"on close"<<endl;
    //messages.push_back("Connection closed");
}

//--------------------------------------------------------------
void TranslationSocket::onIdle( ofxLibwebsockets::Event& args ){
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
    string id     = splitted[0];
    string type = splitted[1];
    string mesg = splitted[2];
    
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
    
    ofLogNotice("send back to server") << args.message;
    server.send( args.message );
    
    
    // is that necessary?
    args.conn.send( args.message );
    
}

translated * TranslationSocket::getTranslatedForID(string uniqueID) {
    
    for( int i=0; i<translations.size(); i++) {
        
        if(uniqueID == translations[i].uniqueID)
            return &translations[i];
        
    }
    
    return NULL;
}
