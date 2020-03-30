#include "ofApp.h"
#include <math.h>

//--------------------------------------------------------------
void ofApp::setup() {
	ofBackground(220);
    
    ofSetVerticalSync(true);
    
    imageGallery = new ImageGalleryTab("image_gallery",100,100);
    imageGallery->load();
    
    videoGallery = new VideoGalleryTab("video_gallery",100,100);
    videoGallery->load();
    

    videoSelector = new PageSelector("Video Gallery",100,100,*videoGallery, 5);
    imageSelector = new PageSelector("Image Gallery",100,100,*imageGallery, 5);
    cameraScreen = new CameraScreen("Camera",ofGetWindowWidth(),ofGetWindowHeight());
    cameraScreen->setup();
    
    vector<Screen*> screens = {imageSelector, videoSelector,cameraScreen};
    
    screenSelector = new ScreenSelector("screen_selector",100,100, screens);
    screenSelector->setup();

	
}

//--------------------------------------------------------------
void ofApp::update() {
    
	screenSelector->update();
     
}

//--------------------------------------------------------------
void ofApp::draw() {

    screenSelector->draw();
    
}

//
// EVENTs
//

//--------------------------------------------------------------
void ofApp::keyPressed(int key) {


}

//--------------------------------------------------------------
void ofApp::keyReleased(int key) {

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y) {

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button) {

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button) {
    
	if (button == 0) { //left mouse button
		
        screenSelector->mousePressed(x, y, button);
    }
    
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button) {
}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h) {

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg) {

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo) {

}
