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


#pragma once

class Gallery : public Screen{
    
    void createPositions();
    void loadImages();
    void loadVideos();
    
    vector<ofVec2f> positions;
    
    int itemWidth, itemHeight, spaceBetween, selectedMedia, currentMedia;
    
    ofDirectory diretory;
    vector<MediaGUI*> medias;
    vector<MediaGUI*> totalMedias;
    
    int currentPage;
    
    XmlManager* xmlManager;
    PlaylistManager* playlistManager;
    
    bool meetFilter(MediaGUI* m);
    
    
    string mediaType;
    float maxLuminance;
    float maxEdge;
    float maxNFaces;
    float maxNObject;
    float maxTexture;
    float maxRythm;
    ofColor color;

public:
    Gallery(string title,int width, int height,int x, int y, int spaceBetween, PlaylistManager* playlistManager);
    void load();
    void drawPage(int selected);
    void draw();
    void mousePressed(int x, int y, int button);
    
    void update();
    
    void filter();
    
    void setSize(int w, int h);
    
    float getNMedia();
    
    string getMediaType(){
        return mediaType;
    }

	MediaGUI* getMedias(int i);
    
    MediaGUI* getSelectedMedia();
    void search(string filename);
    
    void filterByType(string type);
    void filterByMetadata(string label, float value);
    
};

#endif
