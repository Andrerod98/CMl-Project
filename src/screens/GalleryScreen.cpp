//
//  pageSelector.cpp
//  cml-project
//
//  Created by User on 30/03/2020.
//

#include "GalleryScreen.h"
#include "ofMain.h"

using namespace settings;


GalleryScreen::GalleryScreen(string title,int width, int height,int x, int y,int padding, Gallery* gallery):Screen(title, width, height,x,y){
    this->screen = gallery;
    this->nPages = ceil(gallery->getNMedia() / 8);

    
    currentPage = 1; //starts at 1
    
    this->padding = padding;
    
    setup();
}

void GalleryScreen::setup(){
    nextButton.load(FRONT_ARROW_BUTTON);
    backButton.load(BACK_ARROW_BUTTON);
    
    
    filter.load("fonts/Roboto-Medium.ttf", 16);
    ofxDatGuiTheme* theme = new ofxDatGuiTheme();
    theme->init();
    
    
    theme->font.size = 10;
    theme->layout.height = 40;
    theme->font.ptr = ofxSmartFont::add(theme->font.file, theme->font.size);
    searchInput = new ofxDatGuiTextInput("Search", "Write what you want to search...");
    searchInput->setTheme(theme);
    searchInput->setBackgroundColor(settings::MAIN_COLOR);
    searchInput->setLabelColor(settings::FONT_COLOR);
    searchInput->setStripeColor(settings::MAIN_COLOR);
    
    filtersFolder = new ofxDatGuiFolder("Filters", ofColor::white);
    filtersFolder->setTheme(theme);
    filtersFolder->setBackgroundColor(settings::MAIN_COLOR);
    filtersFolder->setLabelColor(settings::FONT_COLOR);
    vector<string> options = {"All", "Videos", "Images"};
    typeMedia = new ofxDatGuiDropdown("All",options);
    typeMedia->setTheme(theme);
    typeMedia->setBackgroundColor(settings::MAIN_COLOR);
    typeMedia->setLabelColor(settings::FONT_COLOR);
    
}

void GalleryScreen::nextPage(){
    currentPage = currentPage < nPages ? currentPage+=1 : currentPage;
    
}

void GalleryScreen::previousPage(){
    currentPage = currentPage != 1 ? currentPage-=1 : currentPage;
}

void GalleryScreen::drawPage(int page){
    
    screen->drawPage(currentPage);
 
    int nextButtonX = getWidth() - padding - 50;
    int nextButtonY = 235+((ofGetHeight()-80 - (padding*2) - 200)/2);
    
    int backButtonX = padding;
    int backButtonY = 235+((ofGetHeight()-80 - (padding*2) - 200)/2);

    if (currentPage == 1 && nPages > 1) {
        nextButton.draw(nextButtonX,nextButtonY, 50, 50);
    }
    else if (currentPage == nPages) {
        backButton.draw(backButtonX,backButtonY, 50, 50);
    }
    else if (currentPage > 1 && nPages > currentPage) {
         nextButton.draw(nextButtonX,nextButtonY, 50, 50);
         backButton.draw(backButtonX,backButtonY, 50, 50);
    }
   
}

void GalleryScreen::draw(){
    
    int start = getX() + 70;
    int end =  ofGetWidth() - 70;
    
    int yPos =(getY() + padding*2) + 140/2 - 25;
    drawPage(currentPage);
    
    ofSetColor(FONT_COLOR);
    filter.drawString("ALL", start  , yPos);
    
    
    searchInput->setPosition(start + 20 + 70, yPos - 20);
    searchInput->setWidth((end - 100)-(start + 20 + 70)- 20 , 90);
    
  
    filtersFolder->setPosition(start + 20 + 70, yPos + 20);
    filtersFolder->setWidth((end - 100)-(start + 20 + 70)- 20, 40);
    filtersFolder->draw();
    
    
    typeMedia->setPosition(end - 100, yPos - 20);
    typeMedia->setWidth(100, 30);
    typeMedia->draw();
    
    searchInput->draw();
     ofSetColor(255);
}

void GalleryScreen::update(){
    
    screen->update();
    searchInput->update();
    filtersFolder->update();
    typeMedia->update();
}

void GalleryScreen::mousePressed(int x, int y, int button) {
    screen->mousePressed(x, y, button);
    
    int nextButtonX = getWidth() - padding - 50;
    int nextButtonY = 235+((ofGetHeight()-80 - (padding*2) - 200)/2);
    
    int backButtonX = padding;
    int backButtonY = 235+((ofGetHeight()-80 - (padding*2) - 200)/2);

    if (x >= backButtonX && x <= backButtonX + 50 && y >= nextButtonY && y <= nextButtonY+50) {
       previousPage();
    }else if (x >= nextButtonX && x <= nextButtonX + 50 && y >= nextButtonY && y <= nextButtonY + 50) {
       nextPage();
    }
}
