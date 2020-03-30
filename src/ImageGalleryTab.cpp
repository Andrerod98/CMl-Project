#include "ImageGalleryTab.h"

ImageGalleryTab::ImageGalleryTab(string title,int width, int height): Screen(title, width, height){
    createPositions();
}

//Loads images from storage
void ImageGalleryTab::load() {
    //Load images
    diretory.listDir("images/of_logos/");
    diretory.allowExt("jpg");
    diretory.sort(); // in linux the file system doesn't return file lists ordered in alphabetical order
    
    //allocate the vector to have as many ofImages as files
    if (diretory.size()) {
        images.assign(diretory.size(), ofImage());
    }
    
    // you can now iterate through the files and load them into the ofImage vector
    for (int i = 0; i < (int)diretory.size(); i++) {
        images[i].load(diretory.getPath(i));
    }
    
    currentImage = 0;

}

void ImageGalleryTab::createPositions(){
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

void ImageGalleryTab::draw(){
    drawSelected(1);
}

//Draws the image gallery
void ImageGalleryTab::drawSelected(int selected) {

    int nrImg = images.size();
    int nrImages = abs(nrImg - (selected-1)*6);
    
    if (nrImages > 6)
        nrImages = 6;
    
    currentImage = selected * 6 - 6;

    
    for (int i = 0; i < nrImages; i++) {
        images[currentImage + i].draw(positions[i], 200, 200);
    }
}

void ImageGalleryTab::setup() {
    
}

void ImageGalleryTab::update(){
    
}

void ImageGalleryTab::mousePressed(int x, int y, int button) {
    
}
