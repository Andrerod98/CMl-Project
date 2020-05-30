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
#include "XmlManager.h"
#include "PlaylistManager.h"
#include "ofxCvHaarFinder.h"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/core/core.hpp"
#include "opencv2/video/video.hpp"
#include "opencv2/imgcodecs/imgcodecs.hpp"


using std::cout;
using std::cerr;
using std::vector;
using std::string;

using cv::Mat;
using cv::Point2f;
using cv::KeyPoint;
using cv::Scalar;
using cv::FastFeatureDetector;
using cv::SimpleBlobDetector;

using cv::DMatch;
using cv::BFMatcher;
using cv::DrawMatchesFlags;
using cv::ORB;



class MediaManager{
    MediaManager();
    ofxCvHaarFinder finder;
    ofDirectory diretory;
    vector<MediaGUI*> medias;
    vector<MediaGUI*> totalMedias;
    
    XmlManager* xmlManager;
    PlaylistManager* playlistManager;
    
    static MediaManager *instance;
    
    int itemWidth, itemHeight,selectedMedia;
    string mediaType;
    float maxLuminance;
    float maxEdge;
    float maxNFaces;
    float maxNObject;
    float maxTexture;
    float maxRythm;
    ofColor color;
public:
    
    static MediaManager *getInstance();
    
    static ofImage processThumbnail(Media* media);
    
    static pair<float, ofColor> processLuminanceAndColor(ofImage image);
    
    static ofColor processColor(Media* media);
    
    int processNFaces(ofImage image);
    
    static float processEdgeDistribution(Media* media);

	static vector<int> processEdges(ofImage image);
    
    static float processTextures(Media* media);
    
    static int processNTimesObject(ofImage image,ofImage media);
    
    Metadata processImage(ofImage image);
    
    static float processRythm(Media* media);
    
    static float processAudioAmplitude(Media* media);
    
    Metadata processMedia(Media* media);

	static float processGabor(ofImage image);
    
    void loadImages();
    
    void loadVideos();
    
    float getNMedia();
    
    void setSize(int w, int h);
    
    MediaGUI* getMedia(int i);
    
    bool meetFilter(MediaGUI* m);
    
    string getMediaType(){
        return mediaType;
    }
    
    MediaGUI* getSelectedMedia();
    int getSelectedMediaIndex();
    
    void search(string filename);
    
    void filter();
    void filterByMetadata(string label, float value);
    void filterByType(string type);
    
    void selectMedia(int i);
};



#endif /* MediaUtils_hpp */
