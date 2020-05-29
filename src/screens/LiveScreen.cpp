//
//  LiveScreen.cpp
//  CMl-Project
//
//  Created by User on 30/04/2020.
//

#include "LiveScreen.h"

LiveScreen::LiveScreen(string title,int width, int height,int x, int y, Camera* camera, PlaylistManager* playlistManager):Screen(title, width, height,x,y){
    
    this->camera = camera;
    this->playlistManager = playlistManager;
    this->camera->registerObserver(this);
    
   

    setPlaylist("#none");
    
}

void LiveScreen::setPlaylist(string name){
    this->currentPlaylist = this->playlistManager->getPlaylist(name);

    this->currentVideo = 0;
    if(currentPlaylist.size() > 0)
        this->media = currentPlaylist.front();
}

void LiveScreen::draw(){
    


    
    if(media == NULL){
        return;
    }
    
    
    
    ofEnableAlphaBlending();

    float alpha = ofGetElapsedTimeMillis() - lastTime;
    
    if(alphaValue > 255)
        alphaValue = 255;
    if(alpha < 1500  && alpha > 0){
        //(((OldValue - OldMin) * (NewMax - NewMin)) / (OldMax - OldMin)) + NewMin0
        
        ofSetColor(255,255,255,alphaValue*2 );

        
    }
    else if(alpha < 3000 ){
        ofSetColor(255,255,255, 255-alphaValue );

    }
    
    
    
    if(media->isImage()){
        (media->getImage())->draw(0,0, getWidth(), getHeight());
    }else if(media->isVideo()){
        
        (media->getVideo())->draw(0,0, getWidth(), getHeight());
    }

    ofDisableAlphaBlending();
}

void LiveScreen::update(){
    if(media == NULL){
        return;
    }
    if(media->isImage()){
        (media->getImage())->update();
    }else if(media->isVideo()){
        (media->getVideo())->update();
    }
    
    
    
    float currentTime = ofGetElapsedTimeMillis();
    float alpha = currentTime - lastTime;
    alphaValue = (((alpha - 0) * (255 - 0)) / (3000 - 0)) + 0;
    
    
    
    if (currentTime - lastTime > 3000){
        cout << "next";
        
       
        if(currentPlaylist.size() == currentVideo){
            
            currentVideo = 0;
       
        }
         this->media = currentPlaylist.at(currentVideo++);
        
        
   
        lastTime = currentTime;
    }
  
}

void LiveScreen::update(Event event) {
    
    switch(event){
            
       
        case NONE:
            setPlaylist("#none");
            break;
        case ONE_PERSON:
            setPlaylist("#one");
            break;
        case TWO_PERSON:
            //setPlaylist("#two");
            break;
        case MULTIPLE_PEOPLE:
            //setPlaylist("#multiple");
            break;
        case MOTION:
            //setPlaylist("#motion");
            break;
        case SOUND:
            //setPlaylist("#sound");
            break;
        default:
            break;
    }
}


void LiveScreen::mousePressed(int x, int y, int button){
    
}


