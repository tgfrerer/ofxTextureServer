#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){
	ofSetVerticalSync(true);
	ofSetFrameRate(2);
	
	// uncomment this to see how preloading a directory works:

	// texServer.preloadDirectory("testImages/");			// this will preload and keep the whole directory,
														// so that further loads requests will return the texture
														// without having to read the image from disk again.
	

	
}

//--------------------------------------------------------------
void testApp::update(){

	int i;
	
	// load a random image file into our first texture. Note that no pixels are loaded, just the texture.
	
	i = random() % 10 + 1;
	texOne = texServer.loadTexture("testImages/" + ofToString(i) + ".jpg");

	// load  a random image file into our second texture. If this image has already been loaded, it is
	// not loaded again, but provided by the ofTextureServer as an ofPtr<ofTexture>
	
	i = random() % 10 + 1;
	texTwo = texServer.loadTexture("testImages/" + ofToString(i) + ".jpg");

	// load a random image file into our third texture.
	
	i = random() % 10 + 1;
	texThree = texServer.loadTexture("testImages/" + ofToString(i) + ".jpg");

	
	// this is where the texServer does the garbage collection.
	// which is why you want to call this at the end of your update method.
	
	texServer.update();
	
}

//--------------------------------------------------------------
void testApp::draw(){

	ofPushStyle();
	ofSetColor(255);

	texOne->draw(100, 100);
	texTwo->draw(texOne->getWidth() + 100 + 10, 100);
	texThree->draw(texTwo->getWidth() + 10 + texOne->getWidth() + 100 + 10, 100);
	
	ofPopStyle();
	
	ofSetColor(255);
	
	// this will draw a debug view of the textureServer,
	// with the original texture image names and their use count.
	// if a texture is retainted 
	
	
	texServer.draw(100,200);

	
}

//--------------------------------------------------------------
void testApp::keyPressed(int key){

}

//--------------------------------------------------------------
void testApp::keyReleased(int key){

}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void testApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void testApp::dragEvent(ofDragInfo dragInfo){ 

}