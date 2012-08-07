#ifndef GUARD_ofxTextureServer
#define GUARD_ofxTextureServer

/*
 *     _____    ___     
 *    /    /   /  /     test_ofxTextureServer
 *   /  __/ * /  /__    (c) ponies & light, 2012. All rights reserved.
 *  /__/     /_____/    poniesandlight.co.uk
 *
 *  ofxTextureServer.h
 *  Created by Tim Gfrerer on 10/01/2012.
 *         
 *  
 */

#include "ofMain.h"

/*
 
 Provides you with an ofPointer to a Texture.
 
 If the texture has not been loaded, it will try to load and initialise it for you, and provide you with an ofPointer to a Texture.
 If the texture was loaded, it will only provide you with an ofPtr to the ofTexture
 
 
 */

class ofxTextureServer {
	map<string, ofPtr<ofTexture> > textureMap;
	map<string, ofPtr<ofTexture> > textureMapRetain;
	
	// we keep one local copy of the failTextureP and only add copies into our map, 
	// so that the placeholder will never be freed, since one copy will always be 
	// retained as a local variable. 
	// This works even when there are no (more) failed elements in the textureMap.
	
	ofPtr<ofTexture> failTextureP;
	bool bOnUpdateIsAttached;
	
public:
	
	ofxTextureServer()
	:bOnUpdateIsAttached(false){
		failTextureP = ofPtr<ofTexture>(new ofTexture());
		failTextureP->allocate(10, 10, GL_RGBA);
		failTextureP->clear();								// make it red so that it will stand out.
	};

	~ofxTextureServer(){

	}
	
	void update(ofEventArgs& args);
	void update();
	void draw(float x=10, float y=0);											// this is only here for debug purposes
	
	void attachTextureServerOnUpdate(){
		ofAddListener(ofEvents().update, this, &ofxTextureServer::update);
		bOnUpdateIsAttached = true;
	};

	void detachTextureServer(){
		if (bOnUpdateIsAttached) ofRemoveListener(ofEvents().update, this, &ofxTextureServer::update);
	};
	
	ofPtr<ofTexture>	loadTexture			(string filename, bool useARBTexure = true, bool retain=false);
	bool				release				(string filename);
	void				preloadDirectory	(string path, bool useArbTexture=true);
	
};


#endif