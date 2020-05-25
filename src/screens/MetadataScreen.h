//
//  MetadataScreen.hpp
//  CMl-Project
//
//  Created by User on 30/04/2020.
//

#ifndef MetadataScreen_h
#define MetadataScreen_h

#include <stdio.h>
#include "Screen.h"
#include "Media.h"
#include "ofxDatGui.h"
#endif /* MetadataScreen_hpp */

class MetadataScreen: public Screen{
    
    MediaGUI* media;
    
    void onTextInputEvent(ofxDatGuiTextInputEvent e);
    
    void setup();
    void drawPlayer();
    
    ofImage playButton;
    ofImage pauseButton;
    ofImage replayButton;
    
    ofxDatGuiLabel* gestures;
    ofxDatGuiLabel* people;
    ofxDatGuiLabel* nPeople;
    ofxDatGuiLabel* object;
    ofxDatGuiLabel* colorPat;
    ofxDatGuiLabel* audio;
    ofxDatGuiTextInput* tags;
    ofxDatGuiButton* saveButton;
    
public:
    MetadataScreen(string title,int width, int height,int x, int y, MediaGUI* media);
    
    void update();
    void mousePressed(int x, int y, int button);
    void draw();
    
};
