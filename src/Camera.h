//
//  CameraUtils.hpp
//  CMl-Project
//
//  Created by User on 21/05/2020.
//

#ifndef CameraUtils_h
#define CameraUtils_h

#include <stdio.h>
#include "ofxCvHaarFinder.h"
#include "Observer.h"
#include "Subject.h"
#include "Events.h"


class Camera: public Subject{

    ofxCvHaarFinder finder;
    
    std::vector<Observer *> observers; // observers
    
    ofVideoGrabber vidGrabber;
    int camWidth;
    int camHeight;
    
    ofxCvColorImage colorImg;
    ofxCvGrayscaleImage     grayImg;
    
    int lastNPeople;
   

public:
    Camera();
    int getNPeople();
    
    void registerObserver(Observer *observer);
    void removeObserver(Observer *observer);
    void notifyObservers(Event event) ;
    void update();
    
    ofVideoGrabber getVideoGrabber();

    //static bool peopleOnCamera();
    //static bool isMotion();
    //static float handGestures();
    //static bool audioDetected();
    //static bool objectRecognized();
    //static bool colorPattern();
    
};

#endif /* CameraUtils_h */
