#ifndef Header_h
#define Header_h

#include <stdio.h>
#include "ofMain.h"
#include "Screen.h"
#include "Events.h"
#include "Subject.h"
#include "ofxDatGui.h"
#include "Media.h"
#include "Settings.h"
#include "XmlManager.h"



class Header : public Screen, public Subject{
    
    ofxDatGuiButton* liveButton;
    ofxDatGuiButton* configButton;
    ofxDatGuiButton* helpButton;
    ofxDatGuiButton* refreshMetadata;
    
    ofImage backButton;
    
    void liveButtonPress(ofxDatGuiButtonEvent e);
    void configButtonPress(ofxDatGuiButtonEvent e);
    void helpButtonPress(ofxDatGuiButtonEvent e);
    void darkButtonPress(ofxDatGuiButtonEvent e);
	void refreshButtonPress(ofxDatGuiButtonEvent e);
    
    void drawMetadataHeader();
    void drawFullHeader();
    void drawTabs();
    
    void setup();
    
    bool isMetadata;
    
    Media* media;
    std::vector<Observer *> observers; // observers
    int currentScreen;
    int nScreens;
    
    std::vector<string> screens;
    
    ofTrueTypeFont title;
    
public:
    Header(string title,int width, int height,int x, int y, vector<string> screens);
    
    void drawSelected(int selected);
    void draw();
    void update();
    void mousePressed(int x, int y, int button);
    
    void registerObserver(Observer *observer);
    void removeObserver(Observer *observer);
    void notifyObservers(Event event) ;
    
    void setMetadataHeader(Media* media);
    void setFullHeader();
    
    void setHeader(Media* media);
    
};

#endif
