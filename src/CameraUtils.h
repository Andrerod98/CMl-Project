//
//  CameraUtils.hpp
//  CMl-Project
//
//  Created by User on 21/05/2020.
//

#ifndef CameraUtils_h
#define CameraUtils_h

#include <stdio.h>


class CameraUtils{
    

         
    static int nPeopleOnCamera();
    static bool peopleOnCamera();
    static bool isMotion();
    static float handGestures();
    static bool audioDetected();
    static bool objectRecognized();
    static bool colorPattern();
    
};

#endif /* CameraUtils_h */
