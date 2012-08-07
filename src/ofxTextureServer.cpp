/*
 *     _____    ___     
 *    /    /   /  /     test_ofxTextureServer
 *   /  __/ * /  /__    (c) ponies & light, 2012. All rights reserved.
 *  /__/     /_____/    poniesandlight.co.uk
 *
 *  ofxTextureServer.cpp
 *  Created by Tim Gfrerer on 10/01/2012.
 *         
 *  
 */

#include "ofxTextureServer.h"

// ----------------------------------------------------------------------

void ofxTextureServer::preloadDirectory(string path, bool useArbTexture){
	// load image elements from given sound directory and retain.
	
	ofDirectory imgDir;
	
	if (path != ""){
		
		// load the actual sound files
		
		imgDir.allowExt("png");
		imgDir.allowExt("jpg");
		imgDir.allowExt("jpeg");
		imgDir.allowExt("PNG");
		imgDir.allowExt("JPG");
		imgDir.allowExt("JPEG");
		
		imgDir.listDir(path);
		vector<ofFile> tmpFiles;
		tmpFiles = imgDir.getFiles();
		
		string dataPath = ofToDataPath(".");
		if (dataPath.length()>0) dataPath = dataPath.substr(0,dataPath.length()-1);
		// path to data path
		
		for (int i=0; i<tmpFiles.size(); i++){
			string filePath = tmpFiles[i].path();
			size_t find_pos = filePath.find(dataPath);
			if (find_pos != string::npos) filePath = filePath.substr(dataPath.length(), filePath.length());
			// this will properly rebase the filePath so that it is relative to the data path, if our file was in the data path.
			
			ofLog(OF_LOG_NOTICE) << "Preloading:" << filePath;
			loadTexture(filePath ,useArbTexture,true);
		}
		
	}
	
}

// ----------------------------------------------------------------------

ofPtr<ofTexture> ofxTextureServer::loadTexture(string filename, bool useArbTexture, bool retain){
	map<string, ofPtr<ofTexture> >::iterator it = textureMap.find(filename);
	
	if (it != textureMap.end()){
		
		// if smart pointer to our texture can be found in our internal collection,
		// return a copy of the pointer to the item in the collection
		
		// attempt to store an additional copy of the ofPtr 
		// internally if we are asked to retain the texture.
		// if the texture has been retained already this will 
		// just overwrite the last ofPtr to the texture with 
		// a new one, keeping the count intact.
		if (retain) textureMapRetain[filename] = it->second;

		
		return it->second;
	} else {

		// else create a new texture, 
		// add it to our internal collection,
		// return a pointer to the item in our internal collection.
		
		
		ofImage tmpImage;
		tmpImage.setUseTexture(false);

		if (tmpImage.loadImage(filename)){
			// create a new texture
			ofTexture * tmpTextureP = new ofTexture();
			// allocate enough space for the texure
			tmpTextureP->allocate(tmpImage.getWidth(), tmpImage.getHeight(), GL_RGBA, useArbTexture);
			// load the temporary image pixels into our texture.
			tmpTextureP->loadData(tmpImage.getPixelsRef());
			// hand the texture pointer over ot a smart pointer which will eventually free the texture.
			ofPtr<ofTexture> textureP(tmpTextureP);
			
			// add to internal map
			textureMap[filename] = textureP;
			// save an additional copy of the ofPtr internally if we are asked to retain the texture.
			if (retain) textureMapRetain[filename] = textureP;
			
			return textureP;

		} else {
			
			ofPtr<ofTexture> tmpFailTexture;
			tmpFailTexture = failTextureP;
			
			textureMap[filename] = tmpFailTexture;
			
			return tmpFailTexture;
			
		}

	}
	
}

// ----------------------------------------------------------------------

bool ofxTextureServer::release(string filename){

	// this method will release a texture with a given filename if it has been previously retained.
	// returns true if texture was freed
	// returns false if texture was not found in textureMapRetain (so maybe it wasn't retained after all)
	
	map<string, ofPtr<ofTexture> >::iterator it = textureMapRetain.find(filename);
	
	if (it != textureMapRetain.end()){
		textureMapRetain.erase(it);
		return true;
	} else {
		return false;
	}
}

// ----------------------------------------------------------------------

void ofxTextureServer::update(){

	// memory --> garbage collection
	
	map<string, ofPtr<ofTexture> >::iterator it = textureMap.begin();

	// remove all shared pointers which are unique (these only exist within this instance's textureMap)
	while (it != textureMap.end()){
		
		if (it->second.unique()){
			// no one is using this texture anymore, getting rid of it
			
			ofLog(OF_LOG_VERBOSE) << "ofxTextureServer: clearing texture: " << it->first;
			
			textureMap.erase(it);
		} else it++;

	}
	
	
}

// ----------------------------------------------------------------------

void ofxTextureServer::update(ofEventArgs& args){
	update();
}

// ----------------------------------------------------------------------

void ofxTextureServer::draw(float x, float y){
	
	// this method should only be called for debug purposes.

	ofPushStyle();
	ofEnableAlphaBlending();
	ofSetColor(0, 66);
	ofRect(x, y, 45*8+2*8, 12*(textureMap.size() + 2) +2*8);

	ofSetColor(255);
	map<string, ofPtr<ofTexture> >::iterator it = textureMap.begin();

	int lineNr = 0;
	
	ofDrawBitmapString(string("ofxTextureServer"), x+8, y + 12 * lineNr);
	
	lineNr = 2;

	while (it != textureMap.end()) {
		
		char outStr[256];
		
		sprintf(outStr, "%-40s: % 3ld", it->first.c_str(), it->second.use_count()-1);

		ofDrawBitmapString(string(outStr), x+8, y + 12 * lineNr + 8);
		
		it++;
		lineNr++;
	}
	ofDisableAlphaBlending();
	ofPopStyle();
}

// ----------------------------------------------------------------------

