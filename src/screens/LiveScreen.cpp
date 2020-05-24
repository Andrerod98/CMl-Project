//
//  LiveScreen.cpp
//  CMl-Project
//
//  Created by User on 30/04/2020.
//

#include "LiveScreen.h"

LiveScreen::LiveScreen(string title,int width, int height,int x, int y, MediaGUI* media, Camera* camera):Screen(title, width, height,x,y){
    this->media = media;
    this->camera = camera;
    this->camera->registerObserver(this);
    
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

void LiveScreen::update(Event event) {
    
    switch(event){
            
       
        case NONE:
            break;
        case ONE_PERSON:
            
            break;
        case TWO_PERSON:
            
            break;
        case MULTIPLE_PEOPLE:
            
            break;
        case MOTION:
            
            break;
        case SOUND:
        
            break;
        default:
            break;
    }
}
void LiveScreen::mousePressed(int x, int y, int button){
    
}


