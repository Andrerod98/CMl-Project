#include "ofApp.h"
#include <math.h>

//--------------------------------------------------------------
void ofApp::setup() {
	ofBackground(220);
	ofSetVerticalSync(true);

	title.load("fonts/Roboto-Medium.ttf", 20);

	title_image = "Images";
	title_video = "Videos";

	pageSelectedImages = true;
	currentPage = 1; //starts at 1
	currentPageV = 1;
	maxPage = 0;
	maxPageV = 0;

	loadImages();
	loadVideos();
	setupPos();

	for (int i = 0; i < videos.size(); i++) {
		videos[i].play();
		videos[i].setPaused(true);

	}
}

//--------------------------------------------------------------
void ofApp::update() {
	if (!pageSelectedImages) {
		for (int i = 0; i < videos.size(); i++) {
			videos[i].update();
		}
	}
}

//--------------------------------------------------------------
void ofApp::draw() {
	drawScreenSelector();
	if (pageSelectedImages) {
		drawImages();
	}
	else {
		drawVideos();
	}
	drawPageNavigator();
}

//
// Setup 
//

//Loads images from storage
void ofApp::loadImages() {
	//Load images
	dirI.listDir("images/of_logos/");
	dirI.allowExt("jpg");
	dirI.sort(); // in linux the file system doesn't return file lists ordered in alphabetical order

	//allocate the vector to have as many ofImages as files
	if (dirI.size()) {
		images.assign(dirI.size(), ofImage());
	}

	// you can now iterate through the files and load them into the ofImage vector
	for (int i = 0; i < (int)dirI.size(); i++) {
		images[i].load(dirI.getPath(i));
	}
	currentImage = 0;
}

//Loads videos from storega
void ofApp::loadVideos() {
	//Load videos
	dirV.listDir("videos/");
	dirV.allowExt("mov");
	dirV.sort();

	//allocate the vector
	if (dirV.size())
		videos.assign(dirV.size(), ofVideoPlayer());

	for (int i = 0; i < (int)dirV.size(); i++) {
		videos[i].load(dirV.getPath(i));
		videos[i].setLoopState(OF_LOOP_NORMAL);
	}
	currentVideo = 0;
}

void ofApp::setupPos() {
	//current collumn
	int j = 0;
	int i = 0;

	//allocate
	positions.assign(6, ofVec2f());

	//fill in
	while ( i < 3) {
		positions[i].set(100 + j * 300, 200);
		positions[i+3].set(100 + j * 300, 500);
		j++;
		i++;
	}
}

//
// Interfaces
//

//Draws the navigation menu
void ofApp::drawScreenSelector() {
	//external container
	int containerHeight = 100;
	int containerWidth = 1000;

	ofSetColor(240);
	ofFill();
	ofDrawRectangle(0, 0, containerWidth, containerHeight);

	//divisor line
	ofSetColor(150);
	ofDrawLine(containerWidth * 0.5, containerHeight * 0.25, containerWidth * 0.5, containerHeight * 0.75);

	//navigtion options
	ofNoFill();
	if (pageSelectedImages) {
		ofSetColor(0);
		//ofDrawRectangle(containerWidth * 0.3, containerHeight * 0.25, containerWidth *0.15, containerHeight * 0.5);
		title.drawString(title_image, (containerWidth * 0.3 + title.stringWidth(title_image) * 0.40), (containerHeight* 0.75 - title.stringHeight(title_image) * 0.5));

		ofSetColor(200);
		//ofDrawRectangle(containerWidth * 0.55, containerHeight * 0.25, containerWidth *0.15, containerHeight * 0.5);
		title.drawString(title_video, (containerWidth * 0.55 + title.stringWidth(title_video) * 0.25), (containerHeight* 0.75 - title.stringHeight(title_video) * 0.5));
	}
	else {
		ofSetColor(200);
		//ofDrawRectangle(containerWidth * 0.3, containerHeight * 0.25, containerWidth *0.15, containerHeight * 0.5);
		title.drawString(title_image, (containerWidth * 0.3 + title.stringWidth(title_image) * 0.40), (containerHeight* 0.75 - title.stringHeight(title_image) * 0.5));

		ofSetColor(0);
		//ofDrawRectangle(containerWidth * 0.55, containerHeight * 0.25, containerWidth *0.15, containerHeight * 0.5);
		title.drawString(title_video, (containerWidth * 0.55 + title.stringWidth(title_video) * 0.25), (containerHeight* 0.75 - title.stringHeight(title_video) * 0.5));
	}
}

//Draws the image gallery
void ofApp::drawImages() {

	int nrImg = images.size();
	int nrImages = abs(nrImg - (currentPage-1)*6);

	if (nrImages > 6)
		nrImages = 6;

	currentImage = currentPage * 6 - 6;	

	for (int i = 0; i < nrImages; i++) {
		images[currentImage + i].draw(positions[i], 200, 200);
	}
}

//Draws the video gallery
void ofApp::drawVideos() {

	int nrVid = videos.size();
	int nrVideos = abs(nrVid - (currentPageV - 1) * 6);

	if (nrVideos > 6)
		nrVideos = 6;

	currentVideo = currentPageV * 6 - 6;

	for (int i = 0; i < nrVideos; i++) {
		ofSetHexColor(0xFFFFFF);
		videos[currentVideo + i].draw(positions[i], 200, 200);
	}
}

//Draws the page arrow navigator
void ofApp::drawPageNavigator() {

	if (pageSelectedImages) {
		maxPage = floor((int)images.size() / 6) + 1;

		ofSetColor(150);
		ofFill();

		if (currentPage == 1 && maxPage > 1) {
			ofDrawTriangle(975, 450, 950, 425, 950, 475);
		}
		else if (currentPage > 1 && maxPage > currentPage) {
			ofDrawTriangle(25, 450, 50, 425, 50, 475);
			ofDrawTriangle(975, 450, 950, 425, 950, 475);
		}
		else if (currentPage == maxPage) {
			ofDrawTriangle(25, 450, 50, 425, 50, 475);
		}
	}
	else {
		maxPageV = floor((int)videos.size() / 6) + 1;

		ofSetColor(150);
		ofFill();

		if (currentPageV == 1 && maxPageV > 1) {
			ofDrawTriangle(975, 450, 950, 425, 950, 475);
		}
		else if (currentPageV > 1 && maxPageV > currentPageV) {
			ofDrawTriangle(25, 450, 50, 425, 50, 475);
			ofDrawTriangle(975, 450, 950, 425, 950, 475);
		}
		else if (currentPageV == maxPageV) {
			ofDrawTriangle(25, 450, 50, 425, 50, 475);
		}
	}
}


//
// EVENTs
//

//--------------------------------------------------------------
void ofApp::keyPressed(int key) {

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key) {

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y) {

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button) {

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button) {
	if (button == 0) { //left mouse button
		if (x >= 25 && x <= 50 && y >= 425 && y <= 475) {
			// clicked on left page navigator arrow
			if (!pageSelectedImages) {
				currentPageV != 1 ? currentPageV-- : currentPageV;
			}
			else {
				currentPage != 1 ? currentPage-- : currentPage;
			}			
		}
		else if (x >= 950 && x <= 975 && y >= 425 && y <= 475) {
			// clicked on right page navigator arrow
			if (!pageSelectedImages) {
				currentPageV< maxPageV ? currentPageV++ : currentPageV;
			}
			else {
				currentPage < maxPage ? currentPage++ : currentPage;
			}
		}
		else if (x >= 300 && x <= 450 && y >= 25 && y <= 75) {
			// clicked on Image Gallegry
			pageSelectedImages = true;
		}
		else if (x >= 550 && x <= 700 && y >= 25 && y <= 75) {
			// clicked on Video Galery
			pageSelectedImages = false;
		}
		else if (pageSelectedImages == false) {
			for (int i = 0; i < positions.size(); i++) {
				int current = (currentPageV - 1) * 6 + i;
				if (current < videos.size()) {
					if (x >= positions[i].x && x <= (positions[i].x + 200) && y >= positions[i].y && y <= (positions[i].y + 200)) {
						videos[current].setPaused(!videos[current].isPaused());
					}
				}
			}
		}
	}
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button) {
}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h) {

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg) {

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo) {

}