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
#include "ofxOpenCv.h"
#include "ofxCv.h"
#include "ofxCvHaarFinder.h"
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>

class MediaUtils{
	
    
    
public:
    
    static ofImage processThumbnail(Media* media);
    
    static float processLuminance(Media* media);
    
    static ofColor processColor(Media* media);
    
    static int processNFaces(Media* media);
    
    static float processEdgeDistribution(Media* media);

	static vector<int> processEdges(ofImage image);
    
    static float processTextures(Media* media);
    
    static int processNTimesObject(ofImage image,Media* media);
    
    static float processRythm(Media* media);
    
    static float processAudioAmplitude(Media* media);
    
	static Metadata processMedia(Media* media);

	static float processGabor(ofImage image);
};



#endif /* MediaUtils_hpp */
