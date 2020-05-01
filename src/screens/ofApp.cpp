#include "ofApp.h"
#include <math.h>
#include "ofxDatGui.h"

void ofApp::setup() {
    ofBackground(settings::SECONDARY_COLOR);
    
    ofSetVerticalSync(true);
    
    int padding = 10;
    int galleryWidth = ofGetWidth()-(padding*4)-100;
    gallery = new Gallery("image_gallery",galleryWidth,ofGetHeight()-settings::HEADER_HEIGHT - (padding*2) - 200,60,250, 30);
    
    galleryScreen = new GalleryScreen("GALLERY", ofGetWidth(),ofGetHeight()-settings::HEADER_HEIGHT,0,settings::HEADER_HEIGHT,20,gallery);
    cameraScreen = new CameraScreen("CAMERA",ofGetWidth(),ofGetHeight()-settings::HEADER_HEIGHT,0,settings::HEADER_HEIGHT);
    
    vector<string> screens = {"GALLERY", "CAMERA"};
    
    header = new Header("screen_selector", ofGetWidth(),settings::HEADER_HEIGHT,0,0, screens);
    
    
    header->registerObserver(this);
    
    
    ofFill();
    ofSetColor(255);
    

    currentScreen = galleryScreen;
    liveMode =  false;
   
    
}

void ofApp::update() {
    
    
    header->update();
    galleryScreen->update();
    cameraScreen->update();
    
    currentScreen->update();
    
}

void ofApp::drawHelp(){
    ofColor TEST_COLOR(44,44,44);
    ofSetColor(TEST_COLOR);
    ofFill();
    ofDrawRectangle(ofGetWidth()/2 - (ofGetWidth()*0.5)/2,80 + 20, ofGetWidth()*0.5, ofGetHeight() * 0.8);
    
}

void ofApp::draw() {
    

    if(!liveMode)
        header->draw();
    
    currentScreen->draw();
    
    ofFill();
    ofSetColor(255);
    
    if(helpShowing)
        drawHelp();
}

void ofApp::update(Event event) {
    
    switch(event){
            
        case GALLERY_TAB_CHANGE:
            
            currentScreen = galleryScreen;
            break;
        case CAMERA_TAB_CHANGE:
            
            currentScreen = cameraScreen;
            break;
        case LIVE_BUTTON_PRESS:
            liveMode = true;
            liveScreen = new LiveScreen("Live", ofGetWidth(),ofGetHeight(),0,0,gallery->getSelectedMedia());
            
            
            currentScreen = liveScreen;
            break;
        case HELP_BUTTON_PRESS:
            helpShowing = !helpShowing;
            break;
        case BACK_BUTTON_PRESS:
            header->setFullHeader();
            currentScreen = galleryScreen;
            break;
        case METADATA_BUTTON_PRESS:
            header->setMetadataHeader(gallery->getSelectedMedia());
            metadataScreen = new MetadataScreen("Metadata", ofGetWidth(),ofGetHeight()-settings::HEADER_HEIGHT,0,settings::HEADER_HEIGHT,gallery->getSelectedMedia());
            
            
            currentScreen = metadataScreen;
            break;
    }
}

//
// EVENTS
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
        
        header->mousePressed(x, y, button);
        currentScreen->mousePressed(x, y, button);
    }
    
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button) {
}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h) {
    
    int padding = 10;
    int galleryWidth = w-(padding*4)-100;
    
    gallery->setSize(galleryWidth,h-settings::HEADER_HEIGHT - (padding*2) - 200);
    
    galleryScreen->setWidth(w);
    galleryScreen->setHeight(h-settings::HEADER_HEIGHT);
    
    cameraScreen->setWidth(w);
    cameraScreen->setHeight(h-settings::HEADER_HEIGHT);
    
    header->setWidth(w);
    header->setHeight(settings::HEADER_HEIGHT);
    
    currentScreen->setWidth(w);
    currentScreen->setHeight(h - settings::HEADER_HEIGHT);
    
    header->setHeader(gallery->getSelectedMedia());

    
}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg) {
    
}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo) {
    
}
