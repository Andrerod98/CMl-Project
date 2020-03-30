#include "VideoGalleryTab.h"

VideoGalleryTab::VideoGalleryTab(string title,int width, int height): Screen(title, width, height){
    createPositions();
}

void VideoGalleryTab::setup(){
    
    for (int i = 0; i < videos.size(); i++) {
        videos[i].play();
        videos[i].setPaused(true);
    }
}

void VideoGalleryTab::createPositions(){
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

//Loads videos from storega
void VideoGalleryTab::load() {
    
    //Load videos
    diretory.listDir("videos/");
    diretory.allowExt("mov");
    diretory.sort();
    
    //allocate the vector
    if (diretory.size())
        videos.assign(diretory.size(), ofVideoPlayer());
    
    for (int i = 0; i < (int)diretory.size(); i++) {
        videos[i].load(diretory.getPath(i));
        videos[i].setLoopState(OF_LOOP_NORMAL);
    }
    currentVideo = 0;
}

void VideoGalleryTab::draw(){
    drawSelected(1);
}

//Draws the video gallery
void VideoGalleryTab::drawSelected(int selected) {
    
    int nrVid = videos.size();
    int nrVideos = abs(nrVid - (selected - 1) * 6);
    
    if (nrVideos > 6)
        nrVideos = 6;
    
    currentVideo = selected-1;
    
    for (int i = 0; i < nrVideos; i++) {
        ofSetHexColor(0xFFFFFF);
        videos[currentVideo*6 + i].draw(positions[i], 200, 200);
    }
}

void VideoGalleryTab::update(){
    for (int i = 0; i < videos.size(); i++) {
        videos[i].update();
    }
}


void VideoGalleryTab::mousePressed(int x, int y, int button) {
    
    for (int i = 0; i < positions.size(); i++) {
        int current = (currentVideo) * 6 + i;
      
        if (current < videos.size()) {
            if (x >= positions[i].x && x <= (positions[i].x + 200) && y >= positions[i].y && y <= (positions[i].y + 200)) {
                
                videos[current].setPaused(!videos[current].isPaused());
            }
        }
    }
}
