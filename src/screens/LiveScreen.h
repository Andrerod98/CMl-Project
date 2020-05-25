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

class LiveScreen: public Screen, public Observer{
    
    MediaGUI* media;
    Camera* camera;
    
public:
    LiveScreen(string title,int width, int height,int x, int y, MediaGUI* media,Camera* camera);
    
    void update();
    void update(Event event);
    void mousePressed(int x, int y, int button);
    void draw();
};


#endif /* LiveScreen_hpp */
