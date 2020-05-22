//
//  MediaUtils.cpp
//  CMl-Project
//
//  Created by User on 21/05/2020.
//

#include "MediaUtils.h"
#include "ofxOpenCv.h"

ofImage MediaUtils::processThumbnail(Media* media) {
	ofVideoPlayer video = *media->getVideo();
	ofImage thumbnail;

	// getting thumbnail (first frame of the video)
	video.setFrame(0);
	thumbnail.setFromPixels(video.getPixels());

	return thumbnail;
}

float MediaUtils::processLuminance(Media* media){
    
}

ofColor MediaUtils::processColor(Media* media){
    
}

int MediaUtils::processNFaces(Media* media){
    
}

float MediaUtils::processEdgeDistribution(Media* media){
    
}

float MediaUtils::processTextures(Media* media){
    
}

int MediaUtils::processNTimesObject(ofImage image,Media* media){
    
}

float MediaUtils::processRythm(Media* media){
    
}

float MediaUtils::processAudioAmplitude(Media* media){
    
}

Metadata MediaUtils::processMedia(Media* media) {
	float luminance = 0.0;
	float sumLuminance = 0.0;

	float edgeDistribution = 0.0;
	float rhythm = 0.0;
	float texture = 0.0;
	float audioAmplitude = 0.0;
	int nFaces = 0;
	int nObject = 0;
	ofColor color;

	if (media->isImage()) {
		ofImage image = *media->getImage();
		float width = image.getWidth();
		float height = image.getHeight();

		// for all pixels
		for (int x = 0; x < width; x++) {
			for (int y = 0; y < height; y++) {
				sumLuminance += image.getColor(x, y).getLightness();
			}
		}

		// average luminance
		luminance = sumLuminance / (width * height);
	}
	else {
		ofVideoPlayer video = *media->getVideo();
		ofImage thumbnail = processThumbnail(media);


	}

	return Metadata(luminance, edgeDistribution, rhythm, texture, audioAmplitude, nFaces, nObject, color);
}

float MediaUtils::processGabor(ofImage image) {
	float result;

	float sigma = 10.0f;
	float gamma = 0.5f;
	cv::Mat kernel;
	cv::Mat input = ofxCv::toCv(image);
	cv::Mat output;
	cv::Size size = cv::Size(5, 5);
}

