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

class LiveScreen: public Screen{
    
    Media* media;
    
public:
    LiveScreen(string title,int width, int height,int x, int y, Media* media);
    
    void update();
    void mousePressed(int x, int y, int button);
    void draw();
};


#endif /* LiveScreen_hpp */
