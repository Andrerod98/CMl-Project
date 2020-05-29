//
//  GalleryTab.hpp
//  cml-project
//
//  Created by User on 27/04/2020.
//


#ifndef Gallery_h
#define Gallery_h


#include <stdio.h>
#include "Screen.h"

#include "Media.h"
#include "XmlManager.h"
#include "PlaylistManager.h"
#include "MediaManager.h"


#pragma once

class Gallery : public Screen{
    
    void createPositions();
   
    
    vector<ofVec2f> positions;
    
    int itemWidth, itemHeight, spaceBetween;
    
    
    
    int currentPage;
    
   
    MediaManager* mediaManager;
    
    
    

public:
    Gallery(string title,int width, int height,int x, int y, int spaceBetween);
    void load();
    void drawPage(int selected);
    void draw();
    void mousePressed(int x, int y, int button);
    
    void update();
    
    void filter();
    
    void setSize(int w, int h);
    
    
    
    
    void search(string filename);
    
    void filterByType(string type);
    void filterByMetadata(string label, float value);
    
};

#endif
