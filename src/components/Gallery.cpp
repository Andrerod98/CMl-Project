//
//  GalleryTab.cpp
//  cml-project
//
//  Created by User on 27/04/2020.
//

#include "Gallery.h"
#include "Settings.h"

const int NIMAGES = 4;

XmlManager *XmlManager::instance = 0;

Gallery::Gallery(string title,int width, int height,int x, int y, int spaceBetween): Screen(title, width, height,x,y){
    
    
    this->mediaManager = mediaManager->getInstance();
    this->itemWidth = (getWidth()-3*spaceBetween)/(NIMAGES);
    this->itemHeight = (getHeight()-spaceBetween)/2;

    this->spaceBetween = spaceBetween;
    
    createPositions();
    
     mediaManager->setSize(itemWidth, itemHeight);

    
   
}

void Gallery::setSize(int w, int h){
    Screen::setWidth(w);
    this->itemWidth = (getWidth()-3*spaceBetween)/(NIMAGES);
    Screen::setHeight(h);
    this->itemHeight = (getHeight()-spaceBetween)/2;
    
    createPositions();
    
    mediaManager->setSize(itemWidth, itemHeight);
}


void Gallery::createPositions(){
    //current collumn
    int j = 0;
    int i = 0;
    
    //allocate
    positions.assign(8, ofVec2f());
    
    //fill in
    while ( i < 4) {
        positions[i].set(getX()+10+ j*itemWidth+j*spaceBetween, getY()+0);
        positions[i+4].set(getX()+10 + j*itemWidth+j*spaceBetween, getY() + itemHeight + spaceBetween);
        j++;
        i++;
    }
}

void Gallery::draw(){
    
}



//TODO
//Draws the image gallery. starts at page 1
void Gallery::drawPage(int page) {
    currentPage = page;
    int nrMedia = mediaManager->getNMedia();
    int nMediasInPage = abs(nrMedia - (page-1)*8);
    
    if (nMediasInPage > 8)
        nMediasInPage = 8;
    
    int mediaStart = (page-1)*8;
    
    
    ofFill();
    ofSetColor(255);

    for (int i = 0; i < nMediasInPage; i++) {
        int currentMediaIndex = mediaStart + i;
        mediaManager->getMedia(currentMediaIndex)->setPosition(positions[i]);
        
        
        if(currentMediaIndex == mediaManager->getSelectedMediaIndex()){
            ofSetColor(settings::FONT_COLOR);
            ofDrawRectRounded(positions[i] - (5), itemWidth + 10, itemHeight + 10, 5);;
            //TODO selected
            ofSetColor(255);
        }
        if(mediaManager->getMedia(currentMediaIndex)->isImage()){
            (mediaManager->getMedia(currentMediaIndex)->getImage())->draw(positions[i], itemWidth, itemHeight);
            
            
        }else if(mediaManager->getMedia(currentMediaIndex)->isVideo()){
            ofSetHexColor(0xFFFFFF);
			ofVideoPlayer* video = mediaManager->getMedia(currentMediaIndex)->getVideo();
			string filename = mediaManager->getMedia(currentMediaIndex)->getFileName();

			if (!video->isPaused())
				(mediaManager->getMedia(currentMediaIndex)->getVideo())->draw(positions[i], itemWidth, itemHeight);
			else { // draw micon
				string thumbPath = xmlManager->getInstance()->getMetadata(filename, false)->getThumbPath();

				vector<ofImage> images = vector<ofImage>(5);

				//Load images
				directory.listDir(thumbPath);
				directory.allowExt("png");
				directory.sort(); // in linux the file system doesn't return file lists ordered in alphabetical order   

				/*images.at(0).load(directory.getPath(0));
				images.at(1).load(directory.getPath(1));
				images.at(2).load(directory.getPath(2));
				images.at(3).load(directory.getPath(3));
				images.at(4).load(directory.getPath(4));*/

				
			}
        }
    }
    
}


void Gallery::update(){
    int nmedias=mediaManager->getNMedia();
    for (int i = 0; i < nmedias; i++) {
        if(mediaManager->getMedia(i)->isVideo()){
            (mediaManager->getMedia(i)->getVideo())->update();
        }
        
    }
}

void Gallery::mousePressed(int x, int y, int button) {
    
    int start = (currentPage-1) * 8;
    int end = (currentPage) * 8;

    if(end > mediaManager->getNMedia())
        end =mediaManager->getNMedia();
    for(int i = start; i < end; i++){

        if(mediaManager->getMedia(i)->inside(x,y)){
            mediaManager->selectMedia(i);
            
            
            if(mediaManager->getMedia(i)->isVideo()){
                (mediaManager->getMedia(i)->getVideo())->setPaused(!(mediaManager->getMedia(i)->getVideo())->isPaused());
            }
        }
        
    }
    
}
