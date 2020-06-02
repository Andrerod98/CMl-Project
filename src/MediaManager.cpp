//
//  MediaUtils.cpp
//  CMl-Project
//
//  Created by User on 21/05/2020.
//

#include "MediaManager.h"

MediaManager *MediaManager::instance = 0;
const double kDistanceCoef = 4.0;
const int kMaxMatchingSize = 50;
using namespace cv;
MediaManager::MediaManager(){
    
    this->xmlManager = xmlManager->getInstance();
    this->playlistManager  = playlistManager->getInstance();
    
    finder.setup("haarcascade_frontalface_default.xml");
    finder.setScaleHaar(2);
    
    loadObjects();
    loadImages();
    loadVideos();
    
    
    mediaType = "0";
    maxLuminance = 1000;
    maxEdge= 1000;
    maxNFaces= 1000;
    maxNObject= 1000;
    maxTexture= 1000;
    maxRythm= 1000;
    color=ofColor::black;
    
    selectedMedia = 0;
}

MediaManager* MediaManager::getInstance() {
    if (!instance)
        instance = new MediaManager();
    return instance;
}

int MediaManager::getSelectedMediaIndex(){
    return selectedMedia;
}

void MediaManager::loadObjects(){
    string path = "objects/";
    ofDirectory dir(path);
    dir.allowExt("jpg");
    dir.listDir();
    dir.sort();
    
    for (int i = 0; i < (int)dir.size(); i++) {
        objects.push_back(dir.getName(i));
        ofImage image;
        image.load(dir.getPath(i));
        objectsImages.push_back(image);
    }
}
//Loads videos from storega
void MediaManager::loadVideos() {
    
    int nVideos = 0;
    //Load videos
    diretory.listDir("videos/");
    diretory.allowExt("mov");
    diretory.sort();
    
	cout << "Processing videos ";
    
    for (int i = 0; i < (int)diretory.size(); i++) {
        ofVideoPlayer* video = new ofVideoPlayer();
        video->load(diretory.getPath(i));
        video->setLoopState(OF_LOOP_NORMAL);
		video->play();
		video->setPaused(true);
		video->update();
        
        Metadata* meta = xmlManager->getMetadata(diretory.getName(i), false);
        
        //thumbnails
  
        ofDirectory dir(meta->getThumbPath());
        dir.allowExt("png");
        dir.listDir();
        dir.sort();
        vector<ofImage> micons= {};
        
        for (int i = 0; i < (int)dir.size(); i++) {
        
            ofImage image;
            image.load(dir.getPath(i));
            micons.push_back(image);
        }
        
        MediaGUI* media = new MediaGUI(video, diretory.getName(i), meta, micons);

		// getting metadata
		if (!xmlManager->exists(diretory.getName(i), false)) {
			cout << ".";
			xmlManager->createMedia(diretory.getName(i), false);
			xmlManager->setMetadata(diretory.getName(i), false, processMedia(media));
			meta = xmlManager->getMetadata(diretory.getName(i), false);
            ofDirectory dir(meta->getThumbPath());
            dir.allowExt("png");
            dir.listDir();
            dir.sort();
            vector<ofImage> micons= {};
            
            for (int i = 0; i < (int)dir.size(); i++) {
                
                ofImage image;
                image.load(dir.getPath(i));
                micons.push_back(image);
            }
			media = new MediaGUI(video, diretory.getName(i), meta, micons);
		}
        
        for(string tag: meta->getTags()){
            playlistManager->addToPlaylist(tag,media);
        }
        
        medias.push_back(media);
        totalMedias.push_back(media);
    }
	cout << " done" << endl;
}

//Loads images from storage
void MediaManager::loadImages() {
    //Load images
    diretory.listDir("images/of_logos/");
    diretory.allowExt("jpg");
    diretory.sort(); // in linux the file system doesn't return file lists ordered in alphabetical order   

	cout << "Processing images ";
    
    // you can now iterate through the files and load them into the ofImage vector
    for (int i = 0; i < (int)diretory.size(); i++) {
        ofImage* image = new ofImage();
        image->load(diretory.getPath(i));

        Metadata* meta = xmlManager->getMetadata(diretory.getName(i), true);        
        MediaGUI* media = new MediaGUI(image, diretory.getName(i), meta);

		// getting metadata
		if (!xmlManager->exists(diretory.getName(i), true)) {
			cout << ".";
			xmlManager->createMedia(diretory.getName(i), true);
			xmlManager->setMetadata(diretory.getName(i), true, processMedia(media));
			meta = xmlManager->getMetadata(diretory.getName(i), true);
			media = new MediaGUI(image, diretory.getName(i), meta);
		}
       
        for(string tag: meta->getTags()){
            playlistManager->addToPlaylist(tag,media);
        }
        medias.push_back(media);
        totalMedias.push_back(media);        
    }
	cout << " done" << endl;
}

void MediaManager::reloadNotify(bool isSoft) {
	notifyObservers(Event::REFRESH_DATA);
	resfreshMode = isSoft;
}

void MediaManager::reloadMedia() {
	ofSleepMillis(5000);
	medias.clear();
	totalMedias.clear();

	if (resfreshMode) {
		// only loads the new files
		cout << "Starting Soft Reload" << endl;
		loadImages();
		loadVideos();
		cout << "Soft Reload completed with success!" << endl;
	}
	else {
		// reloads everything
		if (xmlManager->clearAll()) {
			cout << "Starting Hard Reload" << endl;
			loadImages();
			loadVideos();
			cout << "Hard Reload completed with success!" << endl;
		} 
		else cout << "Error clearing XML file!" << endl;
	}
	notifyObservers(Event::REFRESH_DATA);
}

void MediaManager::selectMedia(int i){
    selectedMedia = i;
}
MediaGUI* MediaManager::getSelectedMedia(){
    return medias[selectedMedia];
}

void MediaManager::setSize(int w, int h){
    
    for(MediaGUI* media: medias){
        media->setSize(w, h);
    }
}

float MediaManager::getNMedia(){
    return medias.size();
}

MediaGUI* MediaManager::getMedia(int i) {
    return medias[i];
}


void MediaManager::filterByType(string type){
    selectedMedia = 0;
    mediaType = type;
    filter();
}

void MediaManager::filterByMetadata(string label, float value){
    
    if(label == "Max Luminance"){
        maxLuminance = value;
    }
    
    if(label == "Max Edge distribution"){
        maxEdge = value;
    }
    
    if(label == "Max NFaces"){
        maxNFaces = value;
    }
    
    if(label == "Max NObject"){
        maxNObject = value;
    }
    
    if(label == "Max Rythm"){
        maxRythm = value;
    }
    
    if(label == "Max Texture"){
        maxTexture = value;
    }
    
    
    
}

void MediaManager::search(string filename){
    selectedMedia = 0;
    medias.clear();
    for(MediaGUI* m : totalMedias){
        
        if(m->getFileName().rfind(filename, 0) == 0){
            if(mediaType == "0"){
                medias.push_back(m);
                
            }else if(mediaType == "1"){
                if(m->isVideo()){
                    medias.push_back(m);
                }
            }else if(mediaType == "2"){
                if(m->isImage()){
                    medias.push_back(m);
                }
            }
        }
    }
}
void MediaManager::filter(){
    selectedMedia = 0;
    medias.clear();
    for(MediaGUI* m : totalMedias){
        
        if(mediaType == "0"){
            if(meetFilter(m))
                medias.push_back(m);
            
        }else if(mediaType == "1"){
            if(m->isVideo()){
                if(meetFilter(m))
                    medias.push_back(m);
            }
        }else if(mediaType == "2"){
            if(m->isImage()){
                if(meetFilter(m))
                    medias.push_back(m);
            }
        }
    }
}

bool MediaManager::meetFilter(MediaGUI* m){
    return m->getMetadata()->getLuminanceValue() < maxLuminance &&
    //m->getMetadata()->getEdgeDistribution() < maxEdge &&
    m->getMetadata()->getFacesNumber() < maxNFaces &&
    //m->getMetadata()->getObjectNumber() < maxNObject &&
    m->getMetadata()->getTextureValue() < maxTexture &&
    m->getMetadata()->getRhythmValue() < maxRythm;
    //m->getMetadata()->getColorValue() == color;
}

/* Static Algorithms */
ofImage MediaManager::processThumbnail(Media* media) {
	ofVideoPlayer video = *media->getVideo();
	ofImage thumbnail;

	// getting thumbnail (first frame of the video)
    
	video.setFrame(10);
	thumbnail.setFromPixels(video.getPixels());

	return thumbnail;
}

pair<float,ofColor> MediaManager::processLuminanceAndColor(ofImage image){
	//Luminance variables
	float luminance = 0.0;
	float sumLuminance = 0.0;

	//Color - based on first moment
	double sumRed, sumGreen, sumBlue;
	sumRed = sumGreen = sumBlue = 0;
	double red, green, blue;
	ofColor color;

	float width = image.getWidth();
	float height = image.getHeight();

	// for all pixels
	for (int x = 0; x < width; x++) {
		for (int y = 0; y < height; y++) {
			color = image.getColor(x, y);
			sumRed += color.r;
			sumGreen += color.g;
			sumBlue += color.b;
			sumLuminance += (0.2125*color.r + 0.7154*color.g + 0.0721*color.b);
		}
	}

	red = sumRed / (width * height);
	green = sumGreen / (width * height);
	blue = sumBlue / (width * height);
	color = ofColor(red, green, blue);
	luminance = sumLuminance / (width * height);

	return pair<float, ofColor>(luminance, color);
}

ofColor MediaManager::processColor(Media* media){
	return ofColor();
}

int MediaManager::processNFaces(ofImage image){
    finder.findHaarObjects(image);
	return finder.blobs.size();
}

float MediaManager::processEdgeDistribution(Media* media){
	return 0.0f;
}

vector<int> MediaManager::processEdges(ofImage input) {
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
    
    float sq2 = std::sqrt(2);
	// 45 degree
	float d45K[2][2] = {
		{ sq2, 0},
		{0, -sq2}
	};
	cv::Mat d45Kernel = cv::Mat(2, 2, CV_32FC1, &d45K);
	// 135 degree
	float d135K[2][2] = {
		{0, sq2},
		{-sq2, 0}
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

	/*
	vImg.save("vImage.png");
	hImg.save("hImage.png");
	d45Img.save("d45Image.png");
	d135Img.save("d135Image.png");
	ndImg.save("ndImage.png");
	*/

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

float MediaManager::processTextures(Media* media){
	return 0.0f;
}

inline void match(Mat& desc1, Mat& desc2, vector<DMatch>& matches) {
    matches.clear();

        BFMatcher desc_matcher(cv::NORM_L2, true);
        vector< vector<DMatch> > vmatches;
        desc_matcher.knnMatch(desc1, desc2, vmatches, 2);
        for (int i = 0; i < matches.size(); ++i)
        {
            const float ratio = 0.8; // As in Lowe's paper; can be tuned
            if (vmatches[i][0].distance < ratio * vmatches[i][1].distance)
            {
                matches.push_back(vmatches[i][0]);
            }
        }
    
}

inline void findKeyPointsHomography(vector<KeyPoint>& kpts1, vector<KeyPoint>& kpts2,
                                    vector<DMatch>& matches, vector<char>& match_mask) {
    if (static_cast<int>(match_mask.size()) < 3) {
        return;
    }
    vector<Point2f> pts1;
    vector<Point2f> pts2;
    for (int i = 0; i < static_cast<int>(matches.size()); ++i) {
        pts1.push_back(kpts1[matches[i].queryIdx].pt);
        pts2.push_back(kpts2[matches[i].trainIdx].pt);
    }
    findHomography(pts1, pts2, cv::RANSAC, 4, match_mask);
}

int MediaManager::processNTimesObject(ofImage image,ofImage media){   
    Mat img_1 = ofxCv::toCv(image);
    Mat img_2 = ofxCv::toCv(media);
    
    cvtColor(img_1, img_1, cv::COLOR_RGB2GRAY);
    cvtColor(img_2, img_2, cv::COLOR_RGB2GRAY);
    Mat descriptors_1;
    Mat descriptors_2;
    std::vector<cv::KeyPoint> keypoints_1, keypoints_2;
    Ptr<ORB> orb = ORB::create();
    orb->detectAndCompute(img_1, Mat(), keypoints_1, descriptors_1);
    orb->detectAndCompute(img_2, Mat(), keypoints_2, descriptors_2);

    // if one of the images has no descriptors return 0
    if (descriptors_1.empty() || descriptors_2.empty()) {
        return 0;
    }

    vector< cv::DMatch>  matches;
    BFMatcher matcher(cv::NORM_L2, true);
    matcher.match(descriptors_1, descriptors_2, matches);

    std::sort(matches.begin(), matches.end());
    while (matches.front().distance * kDistanceCoef < matches.back().distance) {
        matches.pop_back();
    }
    while (matches.size() > kMaxMatchingSize) {
        matches.pop_back();
    }
    
    vector<char> match_mask(matches.size(), 1);
    findKeyPointsHomography(keypoints_1, keypoints_2, matches, match_mask);

    // Return the amount of "good matches"
    return matches.size();
}

float MediaManager::processRythm(Media* media){
	return 0.0f;
}

float MediaManager::processAudioAmplitude(Media* media){
	return 0.0f;
}
Metadata MediaManager::processImage(ofImage image){
    
    //Luminance variables
    float luminance = 0.0;
    float sumLuminance = 0.0;
    
    //Color - based on first moment
    double sumRed, sumGreen, sumBlue;
	sumRed = sumGreen = sumBlue = 0;
    double red, green, blue;
    ofColor color;
    //NFaces
    int nFaces = 0;
    //Edge distribution
    vector<int> edgeDistribution = {};
    //Texture characteristics
    float texture = 0.0;
    //NObject
    vector<int> nObjects = {};
    
    float width = image.getWidth();
    float height = image.getHeight();
    
    // for all pixels
    for (int x = 0; x < width; x++) {
        for (int y = 0; y < height; y++) {
            color = image.getColor(x, y);
            sumRed += color.r;
            sumGreen += color.g;
            sumBlue += color.b;
            sumLuminance += (0.2125*color.r + 0.7154*color.g + 0.0721*color.b);
        }
    }
    
    red = sumRed / (width * height);
    green = sumGreen / (width * height);
    blue = sumBlue / (width * height);
    color = ofColor(red, green, blue);
    luminance = sumLuminance / (width * height);
    nFaces = processNFaces(image);
    edgeDistribution = processEdges(image);
    texture = processGabor(image);
    
   
    
    for(ofImage img: objectsImages){
       
        nObjects.push_back(processNTimesObject(img, image));
    }
    
    return Metadata(luminance, edgeDistribution, 0, texture, 0, nFaces, nObjects, color);
}

int getVariance(Mat hist1, Mat hist2){
    Mat res;
    absdiff(hist1, hist2, res);
    //cout << sum(res)[0] << "\n";
    return sum(res)[0];
}

Metadata MediaManager::processMedia(Media* media) {
	float luminance = 0.0;

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
    
    float frameLuminance = 0;
	pair<float, ofColor> luminanceAndColor;
    
    //Rhythm Variables
   
    float meanRhythm = 0;
    float rhythmFrame = 0;
    vector <float> rhythmPerFrame;
    float rhythmVariations = 0;

    
    int maxFaces = 0;
    int maxObjects = 0;
    float sumLuminance = 0;
	if (media->isImage()) {
		ofImage image = *media->getImage();
        return processImage(image);
	}
	else {
		ofVideoPlayer video = *media->getVideo();
        ofImage image;
		Mat imgSrc;
        vector<int> rythmVariance = {};
        // Establish the number of bins
        int histSize = 256;
        
        // Set the ranges ( for B,G,R) )
        float range[] = { 0, 256 } ;
        const float* histRange = { range };

        int max = video.getTotalNumFrames();
     
        // normalize(current_hist, current_hist, 0, 255, NORM_MINMAX, -1, Mat() );
        Mat current_hist;
        Mat previous_hist;
        Mat imageGrayMat;


		video.play();
		video.setPaused(true);
		video.update();

        for (int i = 0; i < max; i++) {
            video.setFrame(i);
            image.setFromPixels(video.getPixels());
            imageGrayMat = ofxCv::toCv(image);
            cv::cvtColor(imageGrayMat, imageGrayMat, CV_BGR2GRAY);
            
            if(i == 0){
                texture = processGabor(image);
                
                //ofImage thumbnail = processThumbnail(media);
                
                edgeDistribution = processEdges(image);
				//calcHist(&imageGrayMat, 1, 0, Mat(), current_hist, 1, &histSize, &histRange, true, false);
                
            }else {
                                
				//previous_hist = current_hist;
                calcHist( &imageGrayMat, 1, 0, Mat(), current_hist, 1, &histSize, &histRange, true, false );
								
                
                video.previousFrame();
                image.setFromPixels(video.getPixels());
                imageGrayMat = ofxCv::toCv(image);
                cv::cvtColor(imageGrayMat, imageGrayMat, CV_BGR2GRAY);
                calcHist( &imageGrayMat, 1, 0, Mat(), previous_hist, 1, &histSize, &histRange, true, false );
            
                rhythmPerFrame.push_back(getVariance(previous_hist, current_hist));                
            }
            
			luminanceAndColor = processLuminanceAndColor(image);
            sumLuminance += luminanceAndColor.first;
			color = luminanceAndColor.second;
			red += color.r;
			green += color.g;
			blue += color.b;
           
			nFaces = processNFaces(image);
            if (maxFaces < nFaces)
                maxFaces = nFaces;

			/*
                
			string path = "objects/";
			ofDirectory dir(path);
			dir.allowExt("jpg");
			dir.listDir();

			nObject = 0;
			for (int i = 0; i < dir.size(); i++) {
				ofImage img;
				img.load(dir.getPath(i));
				nObject += processNTimesObject(img, image);
			}

            if (maxObjects < nObject)
                maxObjects = nObject;

				*/
            
        }

        // Save average luminance
        luminance = sumLuminance / max;
        
        // Calculate mean of RGB colors of the Video
        redMean    = red  / max;
        greenMean  = green / max;
        blueMean   = blue  / max;
        
        color = ofColor(redMean, greenMean, blueMean);
       
		
        // Calculate mean Rhythm Variation between each frame
        for (int i = 0; i < rhythmPerFrame.size(); i++) {            
            rhythmVariations += rhythmPerFrame.at(i);
        }

		rhythm = rhythmVariations / max;
        
        vector<float> sorted = rhythmPerFrame;
        sort(sorted.begin(), sorted.end(), greater<int>());        
        
        for (int i = 0 ; i < 5; i++) {
            ofImage image;
            
            std::vector<float>::iterator it = std::find(rhythmPerFrame.begin(), rhythmPerFrame.end(), sorted[i]);
            int index = std::distance(rhythmPerFrame.begin(), it);            
            
            video.setFrame(index+1);
            image.setFromPixels(video.getPixels());
            
            string filename = media->getFileName().substr(0, media->getFileName().find("."));
            image.save("thumbnails/" + filename + "/" + filename + to_string(i) + ".png");
            xmlManager->setMetadata(media->getFileName(), false, "thumbnails", "thumbnails/" + filename + "/");
            
            //  settings.setValue("metadata:imageUrl" + std::to_string(c) , imagePath);
        }

		nObject = maxObjects;
		nFaces = maxFaces;
	}
    return Metadata(luminance, edgeDistribution, rhythm, texture, audioAmplitude, nFaces, {}, color);
}

float MediaManager::processGabor(ofImage image) {
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

ofImage MediaManager::drawMicon(string filename, int current) {
	ofImage thumb;
	string thumbPath = xmlManager->getInstance()->getMetadata(filename, false)->getThumbPath();

	//Load images
	directory.listDir(thumbPath);
	directory.allowExt("png");
	directory.sort(); // in linux the file system doesn't return file lists ordered in alphabetical order   

	if (directory.size() != 0) {
		//thumb.load("images/of_logos/DSC09302.jpg");
		thumb.load(directory.getPath(current));
		cout << "currentMicon: " << directory.getPath(current) << endl;
		return thumb;
	}
}

void MediaManager::registerObserver(Observer *observer) {
	observers.push_back(observer);
}

void MediaManager::notifyObservers(Event event) {
	for (Observer *observer : observers) {
		observer->update(event);
	}
}
