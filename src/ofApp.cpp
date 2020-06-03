#include "ofApp.h"

using namespace constants;

void ofApp::setup() {
    ofBackground(SECONDARY_COLOR);
    shortcut.load("fonts/Roboto-Medium.ttf", 26);

    ofSetVerticalSync(true);
    
    int padding = 10;
    int galleryWidth = ofGetWidth()-(padding*4)-100;
    xmlManager = xmlManager->getInstance();
    playlistManager = playlistManager->getInstance();
    mediaManager = mediaManager->getInstance();
	mediaManager->registerObserver(this);
    
    gallery = new Gallery("image_gallery",galleryWidth,ofGetHeight()-HEADER_HEIGHT - (padding*2) - 200,60,250, 30);
    
    galleryScreen = new GalleryScreen("GALLERY", ofGetWidth(),ofGetHeight()-HEADER_HEIGHT,0,HEADER_HEIGHT,20,gallery);
    
    camera = new Camera();
    cameraScreen = new CameraScreen("CAMERA",ofGetWidth(),ofGetHeight()-HEADER_HEIGHT,0,HEADER_HEIGHT, camera);

    liveScreen = new LiveScreen("Live", ofGetWidth(),ofGetHeight(),0,0,camera, playlistManager);
    
    vector<string> screens = {"GALLERY", "CAMERA"};
    
    header = new Header("screen_selector", ofGetWidth(),HEADER_HEIGHT,0,0, screens);
    
    header->registerObserver(this);
    
    ofFill();
    ofSetColor(255);
    
    currentScreen = galleryScreen;
    liveMode =  false;
	refreshShowing = false;
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
    
    ofxDatGuiTheme* theme = new ofxDatGuiTheme();
    theme->init();
    theme->font.size = 10;
    theme->layout.height = 50;
    theme->font.ptr = ofxSmartFont::add(theme->font.file, theme->font.size);
    
    ofSetColor(ofColor::white);
    shortcut.drawString("Shortchuts", ofGetWidth()/2 - (ofGetWidth()*0.5)/2 + 10,80 + 20 +40);
        
    vector<ofxDatGuiLabel*> shortcuts = {
        new ofxDatGuiLabel("Back from live screen: B"),
        new ofxDatGuiLabel("Go to gallery: G"),
        new ofxDatGuiLabel("Go to Camera: C"),
        new ofxDatGuiLabel("Next page: ->"),
        new ofxDatGuiLabel("Previous page: <-"),
        new ofxDatGuiLabel("Help: H"),
        new ofxDatGuiLabel("Live mode: L"),
        new ofxDatGuiLabel("Metadata: M"),
 
    };
    
    for(int i = 0; i < shortcuts.size(); i++){
        shortcuts[i]->setPosition(ofGetWidth()/2 - (ofGetWidth()*0.5)/2 + 10,80 + 20 + 10 + 40 + 50*i);
        shortcuts[i]->setTheme(theme);
        shortcuts[i]->setWidth(ofGetWidth()*0.5 - 30, 10);
        shortcuts[i]->setLabelUpperCase(false);
        shortcuts[i]->draw();
    }
    ofxDatGuiLabel*  sh1 = new ofxDatGuiLabel("Back from live screen: b");
}

void ofApp::drawRefreshData() {
	ofColor TEST_COLOR(44, 44, 44);
	ofSetColor(TEST_COLOR);
	ofFill();
	ofDrawRectangle(ofGetWidth() / 2 - (ofGetWidth()*0.5) / 2, 80 + 20, ofGetWidth()*0.5, ofGetHeight() * 0.8);

	ofxDatGuiTheme* theme = new ofxDatGuiTheme();
	theme->init();
	theme->font.size = 10;
	theme->layout.height = 50;
	theme->font.ptr = ofxSmartFont::add(theme->font.file, theme->font.size);

	ofSetColor(ofColor::white);
	refresh.drawString("Refreshing", ofGetWidth() / 2 - (ofGetWidth()*0.5) / 2 + 10, 80 + 20 + 40);

//	if (refreshShowing)
		
}

void ofApp::draw() {
    if(!liveMode)
        header->draw();
    
    currentScreen->draw();
    
    ofFill();
    ofSetColor(255);
    
    if(helpShowing)
        drawHelp();

	if (refreshShowing)
		drawRefreshData();
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
            header->setMetadataHeader(mediaManager->getSelectedMedia());
            metadataScreen = new MetadataScreen("Metadata", ofGetWidth(),ofGetHeight()-HEADER_HEIGHT,0,HEADER_HEIGHT,mediaManager->getSelectedMedia());           
            currentScreen = metadataScreen;
            break;
		case REFRESH_DATA:
			refreshShowing = !refreshShowing;
			cout << "refreshShowing: " << refreshShowing << endl;
			break;
        default:
            break;
    }
}

//
// EVENTS
//

//--------------------------------------------------------------
void ofApp::keyPressed(int key) {
    
    this->galleryScreen->keyPressed(key);
    this->header->keyPressed(key);
    
    if(liveMode){
        if(key == 'b'){
            currentScreen = galleryScreen;
            liveMode = false;
        }
    }
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key) {
    
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y) {
       this->gallery->mouseMoved(x,y);
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
    
    gallery->setSize(galleryWidth,h-HEADER_HEIGHT - (padding*2) - 200);
    
    galleryScreen->setWidth(w);
    galleryScreen->setHeight(h-HEADER_HEIGHT);
    
    cameraScreen->setWidth(w);
    cameraScreen->setHeight(h-HEADER_HEIGHT);
    cameraScreen->setup();
    
    header->setWidth(w);
    header->setHeight(HEADER_HEIGHT);
    
    
    
    currentScreen->setWidth(w);
    currentScreen->setHeight(h - HEADER_HEIGHT);
    
    liveScreen->setWidth(w);
    liveScreen->setHeight(h);
    
    header->setHeader(mediaManager->getSelectedMedia());

    
}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg) {
    
}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo) {
    
}
