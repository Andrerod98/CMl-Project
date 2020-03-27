#pragma once

#include "ofMain.h"

class ofApp : public ofBaseApp {
public:
	void setup();
	void update();
	void draw();

	void loadImages();
	void loadVideos();
	void setupPos();

	//Draws the navigation menu
	void drawScreenSelector();
	//Draws the image gallery
	void drawImages();
	//Draws the video gallery
	void drawVideos();
	//Draws the page navigator
	void drawPageNavigator();

	void keyPressed(int key);
	void keyReleased(int key);
	void mouseMoved(int x, int y);
	void mouseDragged(int x, int y, int button);
	void mousePressed(int x, int y, int button);
	void mouseReleased(int x, int y, int button);
	void windowResized(int w, int h);
	void dragEvent(ofDragInfo dragInfo);
	void gotMessage(ofMessage msg);

	ofTrueTypeFont title;
	ofTrueTypeFont text;
	string title_image, title_video;
	bool pageSelectedImages;

	vector<ofVec2f> positions;
	ofVec2f pos;

	ofDirectory dirI;
	vector<ofImage> images;

	ofDirectory dirV;
	vector<ofVideoPlayer> videos;

	int currentImage;
	int currentVideo;
	int currentPage;
	int currentPageV;
	int maxPage;
	int maxPageV;
};
