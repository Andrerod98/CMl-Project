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
    
    Media* media;
    
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
public:
    MetadataScreen(string title,int width, int height,int x, int y, Media* media);
    
    void update();
    void mousePressed(int x, int y, int button);
    void draw();
    
};
