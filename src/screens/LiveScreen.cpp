//
//  LiveScreen.cpp
//  CMl-Project
//
//  Created by User on 30/04/2020.
//

#include "LiveScreen.h"

LiveScreen::LiveScreen(string title,int width, int height,int x, int y, MediaGUI* media):Screen(title, width, height,x,y){
    this->media = media;
}

void LiveScreen::draw(){
    if(media->isImage()){
        (media->getImage())->draw(0,0, getWidth(), getHeight());
    }else if(media->isVideo()){
        ofSetHexColor(0xFFFFFF);
        (media->getVideo())->draw(0,0, getWidth(), getHeight());
    }
}

void LiveScreen::update(){
    if(media->isImage()){
        (media->getImage())->update();
    }else if(media->isVideo()){
        (media->getVideo())->update();
    }
}

void LiveScreen::mousePressed(int x, int y, int button){
    
}


