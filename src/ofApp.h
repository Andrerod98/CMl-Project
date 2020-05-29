#pragma once

#include "ofMain.h"

#include "Gallery.h"
#include "GalleryScreen.h"
#include "Header.h"
#include "CameraScreen.h"
#include "ofxDatGui.h"
#include "Events.h"
#include "MetadataScreen.h"
#include "LiveScreen.h"
#include "Settings.h"
#include "MediaManager.h"
#include <math.h>
#include "XmlManager.h"
#include "MediaManager.h"

class ofApp : public ofBaseApp, public Observer {
    
    ofxDatGuiButton* liveButton;
    ofxDatGuiButton* configButton;
    ofxDatGuiButton* helpButton;
    ofxDatGuiToggle* darkButton;
    ofTrueTypeFont shortcut;
    
    Camera* camera;
    
    Screen* currentScreen;
    
    Gallery* gallery;
    
    GalleryScreen* galleryScreen;
    GalleryScreen* videoSelector;
    
    CameraScreen* cameraScreen;
    MetadataScreen* metadataScreen;
    LiveScreen* liveScreen;
    PlaylistManager* playlistManager;
    MediaManager* mediaManager;
    
    Header* header;

    
    void setButtons(int w, int h);
    void drawHeader();
    void drawHelp();
    
    bool helpShowing, liveMode;
public:
    void setup();
    void update();
    void draw();
    
    void keyPressed(int key);
    void keyReleased(int key);
    void mouseMoved(int x, int y);
    void mouseDragged(int x, int y, int button);
    void mousePressed(int x, int y, int button);
    void mouseReleased(int x, int y, int button);
    void windowResized(int w, int h);
    void dragEvent(ofDragInfo dragInfo);
    void gotMessage(ofMessage msg);
    
    virtual void update(Event event) ;
    
    void onButtonEvent(ofxDatGuiButtonEvent e);
    
    
	XmlManager* xmlManager;
};
