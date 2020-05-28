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

Gallery::Gallery(string title,int width, int height,int x, int y, int spaceBetween, PlaylistManager* playlistManager): Screen(title, width, height,x,y){
    
    
    this->itemWidth = (getWidth()-3*spaceBetween)/(NIMAGES);
    this->itemHeight = (getHeight()-spaceBetween)/2;
    this->spaceBetween = spaceBetween;
    this->xmlManager = xmlManager->getInstance();
    this->playlistManager  = playlistManager;
    createPositions();
    currentMedia = 0;
    selectedMedia = 0;
    mediaType = "0";
    maxLuminance = 1000;
    maxEdge= 1000;
    maxNFaces= 1000;
    maxNObject= 1000;
    maxTexture= 1000;
    maxRythm= 1000;
    ofColor color=ofColor::black;
    
    load();
}

void Gallery::setSize(int w, int h){
    Screen::setWidth(w);
    this->itemWidth = (getWidth()-3*spaceBetween)/(NIMAGES);
    Screen::setHeight(h);
    this->itemHeight = (getHeight()-spaceBetween)/2;
    
    createPositions();
    
    for(MediaGUI* media: medias){
        media->setSize(itemWidth, itemHeight);
    }
}


float Gallery::getNMedia(){
    return medias.size();
}

MediaGUI* Gallery::getMedias(int i) {
	return medias[i];
}


bool Gallery::meetFilter(MediaGUI* m){
    return m->getMetadata()->getLuminanceValue() < maxLuminance &&
    m->getMetadata()->getEdgeDistribution() < maxEdge &&
    m->getMetadata()->getFacesNumber() < maxNFaces &&
    m->getMetadata()->getObjectNumber() < maxNObject &&
    m->getMetadata()->getTextureValue() < maxTexture &&
    m->getMetadata()->getRhythmValue() < maxRythm;
    //m->getMetadata()->getColorValue() == color;
}

void Gallery::filter(){
    createPositions();
    currentMedia = 0;
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

void Gallery::search(string filename){
    createPositions();
    currentMedia = 0;
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

void Gallery::filterByMetadata(string label, float value){

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

void Gallery::filterByType(string type){
    mediaType = type;
    filter();
}

void Gallery::load() {
    loadImages();
    loadVideos();
    cout << "Pages loaded:" << medias.size() << "\n";
}

//Loads videos from storega
void Gallery::loadVideos() {
    
    int nVideos = 0;
    //Load videos
    diretory.listDir("videos/");
    diretory.allowExt("mov");
    diretory.sort();
    
    
    for (int i = 0; i < (int)diretory.size(); i++) {
        ofVideoPlayer* video = new ofVideoPlayer();
        video->load(diretory.getPath(i));
        video->setLoopState(OF_LOOP_NORMAL);
        
        Metadata* meta = xmlManager->getMetadata(diretory.getName(i), false);
        
        MediaGUI* media = new MediaGUI(video, diretory.getName(i), meta);
        
        for(string tag: meta->getTags()){
            playlistManager->addToPlaylist(tag,media);
        }
        
        media->setSize(itemWidth, itemHeight);
        medias.push_back(media);
        totalMedias.push_back(media);
    }
    
    
    
    
}
//Loads images from storage
void Gallery::loadImages() {
    //Load images
    diretory.listDir("images/of_logos/");
    diretory.allowExt("jpg");
    diretory.sort(); // in linux the file system doesn't return file lists ordered in alphabetical order
    
    
    
    
    // you can now iterate through the files and load them into the ofImage vector
    for (int i = 0; i < (int)diretory.size(); i++) {
        ofImage* image = new ofImage();
        image->load(diretory.getPath(i));
        
        Metadata* meta = xmlManager->getMetadata(diretory.getName(i), true);
        
        MediaGUI* media = new MediaGUI(image, diretory.getName(i), meta);
        media->setSize(itemWidth, itemHeight);
        for(string tag: meta->getTags()){
            playlistManager->addToPlaylist(tag,media);
        }
        medias.push_back(media);
        totalMedias.push_back(media);
        
    }
    
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

MediaGUI* Gallery::getSelectedMedia(){
    return medias[selectedMedia];
}

//TODO
//Draws the image gallery. starts at page 1
void Gallery::drawPage(int page) {
    currentPage = page;
    int nrMedia = medias.size();
    int nMediasInPage = abs(nrMedia - (page-1)*8);
    
    if (nMediasInPage > 8)
        nMediasInPage = 8;
    
    int mediaStart = (page-1)*8;
    
    
    ofFill();
    ofSetColor(255);

    for (int i = 0; i < nMediasInPage; i++) {
        int currentMediaIndex = mediaStart + i;
        medias[currentMediaIndex]->setPosition(positions[i]);
        
        
        if(currentMediaIndex == selectedMedia){
            ofSetColor(settings::FONT_COLOR);
            ofDrawRectRounded(positions[i] - (5), itemWidth + 10, itemHeight + 10, 5);;
            //TODO selected
            ofSetColor(255);
        }
        if(medias[currentMediaIndex]->isImage()){
            (medias[currentMediaIndex]->getImage())->draw(positions[i], itemWidth, itemHeight);
            
            
        }else if(medias[currentMediaIndex]->isVideo()){
            ofSetHexColor(0xFFFFFF);
            (medias[currentMediaIndex]->getVideo())->draw(positions[i], itemWidth, itemHeight);
        }
    }
    
}


void Gallery::update(){
    for (int i = 0; i < medias.size(); i++) {
        if(medias[i]->isVideo()){
            (medias[i]->getVideo())->update();
        }
        
    }
}

void Gallery::mousePressed(int x, int y, int button) {
    
    int start = (currentPage-1) * 8;
    int end = (currentPage) * 8;

    if(end > medias.size())
        end =medias.size();
    for(int i = start; i < end; i++){

        if(medias[i]->inside(x,y)){
            selectedMedia = i;
            
            
            if(medias[i]->isVideo()){
                (medias[i]->getVideo())->setPaused(!(medias[i]->getVideo())->isPaused());
            }
        }
        
    }
    
}
