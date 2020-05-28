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

vector<int> MediaUtils::processEdges(ofImage input) {
	// the result vector will be the counts of edges: vertical, horizontal, 45 degree diagonal, 135 degree diagonal, non directional
	vector<int> result = vector<int>(5);

	cv::Mat image = ofxCv::toCv(input);
	int ddpeth = -1; //use the same as input
	int threshold = 11; // same as the one in the paper
	int vCount, hCount, d45Count, d135Count, ndCount;
	vCount = hCount = d45Count = d135Count = ndCount = 0;

	// convert image to greyscale
	cv::Mat image_gray;
	cv::cvtColor(image, image_gray, CV_BGR2GRAY);

	// we need to create the kernels for each edge type
	// vertical
	float vK[2][2] = {
		{ 1 , -1},
		{ 1, -1}
	};
	cv::Mat vKernel = cv::Mat(2, 2, CV_32FC1, &vK);
	// horizontal
	float hK[2][2] = {
		{ 1 , 1},
		{-1, -1}
	};
	cv::Mat hKernel = cv::Mat(2, 2, CV_32FC1, &hK);
	// 45 degree
	float d45K[2][2] = {
		{ std::sqrt(2), 0},
		{0, -std::sqrt(2)}
	};
	cv::Mat d45Kernel = cv::Mat(2, 2, CV_32FC1, &d45K);
	// 135 degree
	float d135K[2][2] = {
		{0, std::sqrt(2)},
		{-std::sqrt(2), 0}
	};
	cv::Mat d135Kernel = cv::Mat(2, 2, CV_32FC1, &d135K);
	// non directional
	float ndK[2][2] = {
		{2, -2},
		{-2, 2}
	};
	cv::Mat ndKernel = cv::Mat(2, 2, CV_32FC1, &ndK);

	// create 5 copies of image, each of them applying the kernel filter
	cv::Mat vImage;
	cv::Mat hImage;
	cv::Mat d45Image;
	cv::Mat d135Image;
	cv::Mat ndImage;

	cv::filter2D(image, vImage, ddpeth, vKernel);
	cv::filter2D(image, hImage, ddpeth, hKernel);
	cv::filter2D(image, d45Image, ddpeth, d45Kernel);
	cv::filter2D(image, d135Image, ddpeth, d135Kernel);
	cv::filter2D(image, ndImage, ddpeth, ndKernel);

	// convert back to ofImage
	ofImage vImg;
	ofxCv::toOf(vImage, vImg);
	ofImage hImg;
	ofxCv::toOf(hImage, hImg);
	ofImage d45Img;
	ofxCv::toOf(d45Image, d45Img);
	ofImage d135Img;
	ofxCv::toOf(d135Image, d135Img);
	ofImage ndImg;
	ofxCv::toOf(ndImage, ndImg);

	// loop through all pixels and count pixels with color above threshold
	// since its grey scale, all components have the same value
	ofColor color;
	for (int x = 0; x < input.getWidth(); x++) {
		for (int y = 0; y < input.getHeight(); y++) {
			color = vImg.getColor(x, y);
			if ((int)color.r > threshold)
				vCount++;

			color = hImg.getColor(x, y);
			if ((int)color.r > threshold)
				hCount++;

			color = d45Img.getColor(x, y);
			if ((int)color.r > threshold)
				d45Count++;

			color = d135Img.getColor(x, y);
			if ((int)color.r > threshold)
				d135Count++;

			color = ndImg.getColor(x, y);
			if ((int)color.r > threshold)
				ndCount++;
		}
	}

	// lastly we fill the result array
	result[0] = vCount;
	result[1] = hCount;
	result[2] = d45Count;
	result[3] = d135Count;
	result[4] = ndCount;
	return result;
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
	int red, green, blue;
	red = green = blue = 0;
	float redMean, greenMean, blueMean;
	redMean = greenMean = blueMean = 0.0;

	vector<int> edgeDistribution = {};
	float rhythm = 0.0;
	float texture = 0.0;
	float audioAmplitude = 0.0;
	int nFaces = 0;
	int nObject = 0;
	ofColor color = ofColor(0,0,0);

	if (media->isImage()) {
		ofImage image = *media->getImage();
		float width = image.getWidth();
		float height = image.getHeight();

		// for all pixels
		for (int x = 0; x < width; x++) {
			for (int y = 0; y < height; y++) {
				color = image.getColor(x, y);
				red += color.r;
				green += color.g;
				blue += color.b;
				sumLuminance += (0.2125*color.r + 0.7154*color.g + 0.0721*color.b);
			}
		}

		// average luminance
		luminance = sumLuminance / (width * height);
		redMean = red / (width * height);
		greenMean = green / (width * height);
		blueMean = blue / (width * height);
		texture = processGabor(image);

		// color
		color = ofColor(redMean, greenMean, blueMean);

		// edge distribution
		edgeDistribution = processEdges(image);
	}
	else {
		ofVideoPlayer video = *media->getVideo();
		ofImage thumbnail = processThumbnail(media);

		edgeDistribution = processEdges(thumbnail);
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


