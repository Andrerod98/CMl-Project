//
//  MediaUtils.cpp
//  CMl-Project
//
//  Created by User on 21/05/2020.
//

#include "MediaUtils.h"


ofImage MediaUtils::processThumbnail(Media* media) {
	ofVideoPlayer video = *media->getVideo();
	ofImage thumbnail;

	// getting thumbnail (first frame of the video)
	video.setFrame(0);
	thumbnail.setFromPixels(video.getPixels());

	return thumbnail;
}

float MediaUtils::processLuminance(Media* media){
	return 0.0f;
}

ofColor MediaUtils::processColor(Media* media){
	return ofColor();
}

int MediaUtils::processNFaces(Media* media){
	return 0;
}

float MediaUtils::processEdgeDistribution(Media* media){
	return 0.0f;
}

float MediaUtils::processTextures(Media* media){
	return 0.0f;
}

int MediaUtils::processNTimesObject(ofImage image,Media* media){
	return 0;
}

float MediaUtils::processRythm(Media* media){
	return 0.0f;
}

float MediaUtils::processAudioAmplitude(Media* media){
	return 0.0f;
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
		texture = processGabor(image);
	}
	else {
		ofVideoPlayer video = *media->getVideo();
		ofImage thumbnail = processThumbnail(media);


	}

	return Metadata(luminance, edgeDistribution, rhythm, texture, audioAmplitude, nFaces, nObject, color);
}

float MediaUtils::processGabor(ofImage image) {
	float sumGabor = 0.0f;

	float sigma = 10.0f;
	float gamma = 0.5f;
	float lambda = 20.0f;
	float theta = 0.0f;
	cv::Mat kernel;
	cv::Mat input = ofxCv::toCv(image);
	cv::Mat output;
	cv::Size size = cv::Size(5, 5);
	int count = 0;

	for (lambda = 20.0f; lambda <= 100.0f; lambda += 20.0f) {
		for (theta = 0.0f; theta <= (2.0f * (float)CV_PI); theta += ((float)CV_PI / 4.0f)) {
			kernel = cv::getGaborKernel(size, sigma, theta, lambda, gamma);
			cv::filter2D(input, output, -1, kernel);
			sumGabor += cv::mean(output)[0];
			
			count++;
		}
	}

	// for debug porposes
	//string path = count + "-kernel.png";
	//cv::imwrite(path, output);

	return sumGabor / count;
}

