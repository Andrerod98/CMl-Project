//
//  pageSelector.hpp
//  cml-project
//
//  Created by User on 30/03/2020.
//

#ifndef Gallery_screen_h
#define Gallery_screen_h

#include <stdio.h>

#include "Gallery.h"
#include "ofxDatGui.h"
#include "Constants.h"


class GalleryScreen : public Screen{
    
    ofImage nextButton;
    ofImage backButton;
    
    ofTrueTypeFont filter;
    ofxDatGuiTextInput* searchInput;
    
    ofxDatGuiFolder* filtersFolder;
    ofxDatGuiDropdown* typeMedia;
    
    MediaManager* mediaManager;
    
    void onDropdownEvent(ofxDatGuiDropdownEvent e);
    void onSliderEvent(ofxDatGuiSliderEvent e);
    void onButtonEvent(ofxDatGuiButtonEvent e);
    void onTextInputEvent(ofxDatGuiTextInputEvent e);


    void onColorPickerEvent(ofxDatGuiColorPickerEvent e);
    
    int currentPage;
    int nPages;
    int padding;
    
    Gallery* screen;
    
    
    void drawPage(int page);
public:
    GalleryScreen(string title,int width, int height,int x, int y,int padding, Gallery* gallery);
    
    void setup();
    
    void draw();
    void nextPage();
    void previousPage();
    void update();
    
    void keyPressed(int key);
    void mouseMoved(int x, int y);
    
    void mousePressed(int x, int y, int button);
    
    
};

#endif /* pageSelector_hpp */

