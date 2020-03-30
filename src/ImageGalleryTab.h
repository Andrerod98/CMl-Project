//
//  imageGalleryTab.hpp
//  cml-project
//
//  Created by User on 30/03/2020.
//

#ifndef imageGalleryTab_hpp
#define imageGalleryTab_hpp

#include <stdio.h>
#include "ofMain.h"
#include "Screen.h"

class ImageGalleryTab : public Screen{
public:
    ImageGalleryTab(string title,int width, int height);
    void load();
    void drawSelected(int selected);
    void draw();
    void mousePressed(int x, int y, int button);
    void setup();
    void update();
    
    ofDirectory diretory;
    vector<ofImage> images;
    
    int currentImage;
private:
    void createPositions();
    
    vector<ofVec2f> positions;
};


#endif

