#include "ofApp.h"

void ofApp::setup() {
    ofBackground(settings::SECONDARY_COLOR);
    
    ofSetVerticalSync(true);
    
    int padding = 10;
    int galleryWidth = ofGetWidth()-(padding*4)-100;
    xml = xml->getInstance();
    
    playlistManager = new PlaylistManager();
    
    gallery = new Gallery("image_gallery",galleryWidth,ofGetHeight()-settings::HEADER_HEIGHT - (padding*2) - 200,60,250, 30, playlistManager);
    
    cout << "starting algorithm" << endl;
    
    auto start = std::chrono::high_resolution_clock::now();
    // populate xml with loaded medias
    for (int i = 0; i < gallery->getNMedia(); i++) {
        
        if (!xml->exists(gallery->getMedias(i)->getFileName(), gallery->getMedias(i)->isImage())) {
            xml->createMedia(gallery->getMedias(i)->getFileName(), gallery->getMedias(i)->isImage());
            xml->setMetadata(gallery->getMedias(i)->getFileName(), gallery->getMedias(i)->isImage(), MediaUtils::processMedia(gallery->getMedias(i)));
        }
        
    }
    
    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);
    cout << "execution time: " << duration.count() << " miliseconds" << endl;
    
    
    
    
    
    
    
    galleryScreen = new GalleryScreen("GALLERY", ofGetWidth(),ofGetHeight()-settings::HEADER_HEIGHT,0,settings::HEADER_HEIGHT,20,gallery);
    
    camera = new Camera();
    cameraScreen = new CameraScreen("CAMERA",ofGetWidth(),ofGetHeight()-settings::HEADER_HEIGHT,0,settings::HEADER_HEIGHT, camera);
    
    
    
    liveScreen = new LiveScreen("Live", ofGetWidth(),ofGetHeight(),0,0,camera, playlistManager);
    
    
    
    vector<string> screens = {"GALLERY", "CAMERA"};
    
    header = new Header("screen_selector", ofGetWidth(),settings::HEADER_HEIGHT,0,0, screens);
    
    
    header->registerObserver(this);
    
    
    ofFill();
    ofSetColor(255);
    

    currentScreen = galleryScreen;
    liveMode =  false;

   
	
	


	/* xml testing... TODO: remove

	cout << "xml teste: " << xml->setMetadata("DSC09302.jpg", true, "color", "green") << endl;
	string myints[] = { "ola", "adeus" };
	std::list<string> fifth(myints, myints + sizeof(myints) / sizeof(string));
	cout << "xml tag teste: " << xml->setTags("DSC09302.jpg", true, fifth) << endl;

	map <string, string>meta = xml->getMetadata("DSC09302.jpg", true);
	for ( map<string,string>::iterator i = meta.begin(); i!=meta.end(); ++i)
		cout << "Metadata read: tag: " << i->first << " value: " << i->second << endl;
	
	list<string> tags = xml->getTags("DSC09302.jpg", true);
	for (list<string>::iterator i = tags.begin(); i != tags.end(); ++i) {
		cout << "tag: " << *i << endl;
	}


	
	xml->createMedia("randomImage", true);
	xml->createMedia("novaImagem", true);
	xml->createMedia("novovideo", false);
	xml->createMedia("DSC09302", true);
	cout << "xml teste: " << xml->setMetadata("DSC09302", true, "teste", "verificado!") << endl;

	string myints[] = {  "ola", "adeus" };
	std::list<string> fifth(myints, myints + sizeof(myints) / sizeof(string));
	cout << "xml tag teste: " << xml->setTags("novaImagem", true, fifth) << endl;
	*/
	
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
        default:
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
    cameraScreen->setup();
    
    header->setWidth(w);
    header->setHeight(settings::HEADER_HEIGHT);
    
    
    
    currentScreen->setWidth(w);
    currentScreen->setHeight(h - settings::HEADER_HEIGHT);
    
    liveScreen->setWidth(w);
    liveScreen->setHeight(h);
    
    header->setHeader(gallery->getSelectedMedia());

    
}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg) {
    
}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo) {
    
}
