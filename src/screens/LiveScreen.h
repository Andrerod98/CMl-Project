//
//  LiveScreen.hpp
//  CMl-Project
//
//  Created by User on 30/04/2020.
//

#ifndef LiveScreen_h
#define LiveScreen_h

#include <stdio.h>
#include "Screen.h"
#include "Media.h"
#include "Camera.h"
#include "PlaylistManager.h"


class LiveScreen: public Screen, public Observer{
    
    MediaGUI* media;
    Camera* camera;
    PlaylistManager* playlistManager;
    void setPlaylist(string name);
   
    
    
    int alphaValue;

    int currentVideo;
    float lastTime;
    
    MediasVector currentPlaylist;
    
public:
    LiveScreen(string title,int width, int height,int x, int y,Camera* camera,PlaylistManager* playlistManager);
    
    void update();
    void update(Event event);
    void mousePressed(int x, int y, int button);
    void draw();
};


#endif /* LiveScreen_hpp */
