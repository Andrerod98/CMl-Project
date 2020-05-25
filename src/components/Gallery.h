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


#pragma once

class Gallery : public Screen{
    
    void createPositions();
    void loadImages();
    void loadVideos();
    
    vector<ofVec2f> positions;
    
    int itemWidth, itemHeight, spaceBetween, selectedMedia, currentMedia;
    
    ofDirectory diretory;
    vector<MediaGUI*> medias;
    
    int currentPage;
    
    XmlManager* xmlManager;
public:
    Gallery(string title,int width, int height,int x, int y, int spaceBetween, XmlManager* xmlManager);
    void load();
    void drawPage(int selected);
    void draw();
    void mousePressed(int x, int y, int button);
    
    void update();
    
    void setSize(int w, int h);
    
    float getNMedia();

	MediaGUI* getMedias(int i);
    
    MediaGUI* getSelectedMedia();
    
};

#endif
