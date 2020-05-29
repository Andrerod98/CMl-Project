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



class MediaManager{
    MediaManager();
    
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
