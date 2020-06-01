//
//  CameraUtils.cpp
//  CMl-Project
//
//  Created by User on 21/05/2020.
//

#include "Camera.h"

Camera::Camera(){
    finder.setup("haarcascade_frontalface_default.xml");
    finder.setScaleHaar(2);
    
    camWidth = 320;
    camHeight = 240;
    
    vidGrabber.setVerbose(true);
    vidGrabber.setup(camWidth,camHeight);
    
    lastNPeople = 0;
}
ofVideoGrabber Camera::getVideoGrabber(){
    return vidGrabber;
}
void Camera::update(){
    vidGrabber.update();
    

    if (vidGrabber.isFrameNew()){
        
        ofImage image;

        image.setFromPixels(vidGrabber.getPixels());
        grayImg = colorImg;
        finder.findHaarObjects(image);
        
        if(finder.blobs.size() != lastNPeople){
            lastNPeople = finder.blobs.size();
            switch (finder.blobs.size()) {
                case 0:
                 
                    notifyObservers(Event::NONE);
                    break;
                case 1:
               
                    notifyObservers(Event::ONE_PERSON);
                    break;
                case 2:
            
                    notifyObservers(Event::TWO_PERSON);
                    break;
                default:
            
                    notifyObservers(Event::MULTIPLE_PEOPLE);
                    break;
            }
        }
        
    }
}


int Camera::getNPeople(){

    return finder.blobs.size();
}

void Camera::registerObserver(Observer *observer) {
    
    observers.push_back(observer);
    
}

void Camera::removeObserver(Observer *observer) {
    // find the observer
    auto iterator = std::find(observers.begin(), observers.end(), observer);
    
    if (iterator != observers.end()) { // observer found
        observers.erase(iterator); // remove the observer
    }
}

void Camera::notifyObservers(Event event) {
    
    for (Observer *observer : observers) { // notify all observers
        
        observer->update(event);
    }
}
