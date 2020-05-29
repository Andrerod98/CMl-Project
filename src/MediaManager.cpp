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


//Loads videos from storega
void MediaManager::loadVideos() {
    
    int nVideos = 0;
    //Load videos
    diretory.listDir("videos/");
    diretory.allowExt("mov");
    diretory.sort();
    
	cout << "Processing videos";
    
    for (int i = 0; i < (int)diretory.size(); i++) {
        ofVideoPlayer* video = new ofVideoPlayer();
        video->load(diretory.getPath(i));
        video->setLoopState(OF_LOOP_NORMAL);
        
        Metadata* meta = xmlManager->getMetadata(diretory.getName(i), false);        
        MediaGUI* media = new MediaGUI(video, diretory.getName(i), meta);

		// getting metadata
		if (!xmlManager->exists(diretory.getName(i), true)) {
			cout << ".";
			xmlManager->createMedia(diretory.getName(i), false);
			xmlManager->setMetadata(diretory.getName(i), false, processMedia(media));
			meta = xmlManager->getMetadata(diretory.getName(i), false);
			media = new MediaGUI(video, diretory.getName(i), meta);
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
    m->getMetadata()->getObjectNumber() < maxNObject &&
    m->getMetadata()->getTextureValue() < maxTexture &&
    m->getMetadata()->getRhythmValue() < maxRythm;
    //m->getMetadata()->getColorValue() == color;
}

/* Static Algorithms */
ofImage MediaManager::processThumbnail(Media* media) {
	ofVideoPlayer video = *media->getVideo();
	ofImage thumbnail;

	// getting thumbnail (first frame of the video)
    
	video.setFrame(0);
	thumbnail.setFromPixels(video.getPixels());

	return thumbnail;
}

float MediaManager::processLuminance(Media* media){
	return 0.0f;
}

ofColor MediaManager::processColor(Media* media){
	return ofColor();
}

int MediaManager::processNFaces(ofImage image){

    ofxCvGrayscaleImage     grayImg;
    
    grayImg = image;
    finder.findHaarObjects(grayImg);
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
    double red, green, blue;
    ofColor color;
    //NFaces
    int nFaces = 0;
    //Edge distribution
    vector<int> edgeDistribution = {};
    //Texture characteristics
    float texture = 0.0;
    //NObject
    int nObjects = 0;
    
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
    
    string path = "objects/";
    ofDirectory dir(path);
    dir.allowExt("jpg");
    dir.listDir();
    
    for(int i = 0; i < dir.size(); i++){
        ofImage img;
        img.load(dir.getPath(i));
        nObjects = processNTimesObject(img, image);
    }
    
    return Metadata(luminance, edgeDistribution, 0, texture, 0, nFaces, nObjects, color);

    
}

int getVariance(Mat hist1, Mat hist2){
    Mat res;
    absdiff(hist1, hist2, res);
    cout << sum(res)[0] << "\n";
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
    //Color Variables
   
    double reds = 0;
    double greens = 0;
    double blues = 0;
    float meanReds = 0;
    float meanGreens = 0;
    float meanBlues = 0;
    
    //Rhythm Variables
   
    float meanRhythm = 0;
    float rhythmFrame = 0;
    vector <float> rhythmPerFrame;
    vector <float> rhythmVariations;

    
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
        vector<int> rythmVariance = {};
        /// Establish the number of bins
        int histSize = 256;
        
        /// Set the ranges ( for B,G,R) )
        float range[] = { 0, 256 } ;
        const float* histRange = { range };

        int max = video.getTotalNumFrames();
        

        
        
        
       
     
        //normalize(current_hist, current_hist, 0, 255, NORM_MINMAX, -1, Mat() );
        Mat current_hist;
        Mat previous_hist;
        Mat image_gray;
   
        for (int i = 0; i < max; i++) {
            video.setFrame(i);
            image.setFromPixels(video.getPixels());
            image_gray = ofxCv::toCv(image);
            cv::cvtColor(image_gray, image_gray, CV_BGR2GRAY);
            
           // Metadata metadata = processImage(image);
            

       
            
            if(i == 0){
              //  color = metadata.getColorValue();
               // texture = metadata.getTextureValue();
                calcHist( &image_gray, 1, 0, Mat(), previous_hist, 1, &histSize, &histRange, true, false );
                /*
                ofPixels pixels = video.getPixels();
                
                ofImage thumbnail = processThumbnail(media);
                
                thumbnail.save("teste.jpg");
                
                edgeDistribution = processEdges(thumbnail);
                */
            }else{
                calcHist( &image_gray, 1, 0, Mat(), current_hist, 1, &histSize, &histRange, true, false );
                rythmVariance.push_back(getVariance(previous_hist, current_hist));
                previous_hist = current_hist.clone();
            }
            
            
            /*
            sumLuminance += metadata.getLuminanceValue();
           
            if (maxFaces < metadata.getFacesNumber())
                maxFaces = metadata.getFacesNumber();
                
            if (maxObjects < metadata.getObjectNumber())
                maxObjects = metadata.getObjectNumber();
            */
            
        }
        

     
        // Save average luminance
        luminance = sumLuminance / video.getTotalNumFrames();

        
        // Calculate mean of RGB colors of the Video
      /*  meanReds    = reds  / (video.getTotalNumFrames() * image.getWidth() * image.getHeight());
        meanGreens  = greens / (video.getTotalNumFrames() * image.getWidth() * image.getHeight());
        meanBlues   = blues  / (video.getTotalNumFrames() * image.getWidth() * image.getHeight());
        
        color = ofColor(meanReds, meanGreens, meanBlues);
       
        // Calculate Rhythm Variations between each frame (based on luminance)
        for (int i = 1; i < rhythmPerFrame.size(); i++) {
            
            float variation = std::abs(rhythmPerFrame.at(i - 1) - rhythmPerFrame.at(i));
            rhythmVariations.push_back(variation);
            rhythm += variation;
        }
        
        // Calculate Mean Rhythm
        rhythm = rhythm / ( rhythmPerFrame.size() - 1 );
        
   
        
        // CUT DETECTION
        // The greater the rhythm variation the better the frame is suited to become a "key" Frame
        // initialize original index locations
        vector<size_t> idx(rhythmVariations.size());
        iota(idx.begin(), idx.end(), 0);
        
        // sort indexes based on comparing values in rhythmVariations
        sort(idx.begin(), idx.end(),
             [&rhythmVariations](size_t i1, size_t i2) {return rhythmVariations[i1] < rhythmVariations[i2]; });
        
        
        // For the 5 frames with the greatest variations save the images for moving icons
        for (int i = idx.size()-1, c = 0; c < 5 ; c++, i--) {
            
            video.setFrame(idx.at(i));
            image.setFromPixels(video.getPixels());

            
            image.save("thumbnails/" + media->getFileName() + to_string(c) + ".png");
            
          //  settings.setValue("metadata:imageUrl" + std::to_string(c) , imagePath);
        }
         */
        

    
	}
    
    /*
    
    string path = "objects/";
    ofDirectory dir(path);
    //only show png files
    dir.allowExt("jpg");
    //populate the directory object
    dir.listDir();
    
    //go through and print out all the paths
    
    for(int i = 0; i < dir.size(); i++){
        ofImage image;
        image.load(dir.getPath(i));
        nObject = processNTimesObject(image, media);
        cout << "Object:" << nObject;
    }
*/
	return Metadata(luminance, edgeDistribution, rhythm, texture, audioAmplitude, nFaces, nObject, color);
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


