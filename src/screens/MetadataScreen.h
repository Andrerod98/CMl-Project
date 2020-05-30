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
#include "XmlManager.h"
#endif /* MetadataScreen_hpp */

class MetadataScreen: public Screen{
    
    MediaGUI* media;
    
    void onTextInputEvent(ofxDatGuiTextInputEvent e);
    
    void setup();
    void drawPlayer();
    
    ofImage playButton;
    ofImage pauseButton;
    ofImage replayButton;
    
    ofxDatGuiLabel* luminance;
    ofxDatGuiDropdown* edgeDistribution;
    ofxDatGuiLabel* rythm;
    ofxDatGuiLabel* texture;
    ofxDatGuiLabel* nFaces;
    ofxDatGuiLabel* nObject;
    ofxDatGuiLabel* colorLabel;
    ofxDatGuiLabel* audioAmplitude;
    ofxDatGuiLabel* tagsLabel;
     ofRectangle* color;
    ofxDatGuiTextInput* tags;
    ofxDatGuiButton* saveButton;
    
    static vector<string> split(const string& str, const string& delim);

    
public:
    MetadataScreen(string title,int width, int height,int x, int y, MediaGUI* media);
    
    void update();
    void mousePressed(int x, int y, int button);
    void draw();

    
};
