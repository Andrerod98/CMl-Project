//
//  MediaUtils.hpp
//  CMl-Project
//
//  Created by User on 21/05/2020.
//

#ifndef MediaUtils_h
#define MediaUtils_h

#include <stdio.h>
#include "Metadata.h"
#include "Media.h"

class MediaUtils{
    
    
    
public:
    
    static ofImage processThumbnail(Media* media);
    
    static float processLuminance(Media* media);
    
    static ofColor processColor(Media* media);
    
    static int processNFaces(Media* media);
    
    static float processEdgeDistribution(Media* media);
    
    static float processTextures(Media* media);
    
    static int processNTimesObject(ofImage image,Media* media);
    
    static float processRythm(Media* media);
    
    static float processAudioAmplitude(Media* media);
    

};



#endif /* MediaUtils_hpp */
