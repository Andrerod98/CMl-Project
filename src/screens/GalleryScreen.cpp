//
//  pageSelector.cpp
//  cml-project
//
//  Created by User on 30/03/2020.
//

#include "GalleryScreen.h"
#include "ofMain.h"

using namespace constants;


GalleryScreen::GalleryScreen(string title,int width, int height,int x, int y,int padding, Gallery* gallery):Screen(title, width, height,x,y){
    
    mediaManager = mediaManager->getInstance();
    
    this->screen = gallery;
    this->nPages = ceil(mediaManager->getNMedia() / 8);

    
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
    searchInput->setBackgroundColor(MAIN_COLOR);
    searchInput->setLabelColor(FONT_COLOR);
    searchInput->setStripeColor(MAIN_COLOR);
    searchInput->onTextInputEvent(this, &GalleryScreen::onTextInputEvent);
    
    theme->layout.labelWidth = 200;
    theme->layout.width = 200;
    filtersFolder = new ofxDatGuiFolder("Filters", ofColor::white);
    filtersFolder->setTheme(theme);
    filtersFolder->setBackgroundColor(MAIN_COLOR);
    filtersFolder->setLabelColor(FONT_COLOR);
    filtersFolder->setWidth(200,200);
    ofxDatGuiSlider* maxLuminance = filtersFolder->addSlider("Max Luminance", 0, 200);
    ofxDatGuiSlider* maxEdge= filtersFolder->addSlider("Max Edge distribution", 0, 200);
    ofxDatGuiSlider* maxNFaces=filtersFolder->addSlider("Max NFaces", 0, 200);
    ofxDatGuiSlider* maxNObject=filtersFolder->addSlider("Max NObject", 0, 200);
    ofxDatGuiSlider* maxRythm =filtersFolder->addSlider("Max Rythm", 0, 200);
    ofxDatGuiSlider* maxTexture=filtersFolder->addSlider("Max Texture", 0, 200);
    ofxDatGuiColorPicker* color= filtersFolder->addColorPicker("Color:");
    filtersFolder->addButton("Apply");
    filtersFolder->onSliderEvent(this, &GalleryScreen::onSliderEvent);
    filtersFolder->onColorPickerEvent(this, &GalleryScreen::onColorPickerEvent);
    filtersFolder->onButtonEvent(this, &GalleryScreen::onButtonEvent);
    
    vector<string> options = {"All", "Videos", "Images"};
    typeMedia = new ofxDatGuiDropdown("All",options);
    typeMedia->setTheme(theme);
    typeMedia->setBackgroundColor(MAIN_COLOR);
    typeMedia->setLabelColor(FONT_COLOR);
    typeMedia->onDropdownEvent(this, &GalleryScreen::onDropdownEvent);
}

void GalleryScreen::onTextInputEvent(ofxDatGuiTextInputEvent e)
{
    // text input events carry the text of the input field //
    cout << "From Event Object: " << e.text << endl;
    // although you can also retrieve it from the event target //
    cout << "From Event Target: " << e.target->getText() << endl;
    this->mediaManager->search(e.text);
    currentPage = 1;
    this->nPages = ceil(mediaManager->getNMedia() / 8);
}


void GalleryScreen::onButtonEvent(ofxDatGuiButtonEvent e)
{
    cout << e.target->getName();
    this->mediaManager->filter();
    currentPage = 1;
    this->nPages = ceil(mediaManager->getNMedia() / 8);
    filtersFolder->collapse();
    searchInput->setText("Write what you want to search...");
    
}

void GalleryScreen::onSliderEvent(ofxDatGuiSliderEvent e)
{
    cout << e.target->getName();
    this->mediaManager->filterByMetadata(e.target->getName(), e.value);


}

void GalleryScreen::onColorPickerEvent(ofxDatGuiColorPickerEvent e)
{
    //cout <<to_string(e.color);
  
    
}

void GalleryScreen::onDropdownEvent(ofxDatGuiDropdownEvent e)
{
    cout <<to_string(e.child);
    mediaManager->filterByType(to_string(e.child));
    currentPage = 1;
    this->nPages = ceil(mediaManager->getNMedia() / 8);
 
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
    else if (currentPage == nPages && currentPage > 1) {
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
    string filterText = "";
    if(this->mediaManager->getMediaType() == "0")
        filterText = "ALL";
    else if(this->mediaManager->getMediaType() == "1")
        filterText = "VIDEOS";
    else if(this->mediaManager->getMediaType() == "2")
        filterText = "IMAGES";
    
    filter.drawString(filterText, start  , yPos);
    
    
    searchInput->setPosition(start + 20 + 70, yPos - 20);
    searchInput->setWidth((end - 100)-(start + 20 + 70)- 20 , 90);
    
  
    filtersFolder->setPosition(start + 20 + 70, yPos + 20);
    filtersFolder->setWidth((end - 100)-(start + 20 + 70)- 20, 200);
    filtersFolder->draw();
    
    
    typeMedia->setPosition(end - 100, yPos - 20);
    typeMedia->setWidth(100, 30);
    typeMedia->draw();
    
    searchInput->draw();
     ofSetColor(255);
}

void GalleryScreen::update(){
	if (nPages != ceil(mediaManager->getNMedia() / 8)) {
		nPages = ceil(mediaManager->getNMedia() / 8);
		currentPage = 1;
	}


    screen->update();
    searchInput->update();
    filtersFolder->update();
    typeMedia->update();
}
void GalleryScreen::keyPressed(int key) {
    if (key == OF_KEY_RIGHT) {
        nextPage();
    } else if (key == OF_KEY_LEFT) {
        previousPage();
    } else if (key == 'a') {
        mediaManager->filterByType("0");
        currentPage = 1;
        this->nPages = ceil(mediaManager->getNMedia() / 8);
    } else if (key == 'v') {
        mediaManager->filterByType("1");
        currentPage = 1;
        this->nPages = ceil(mediaManager->getNMedia() / 8);
    } else if (key == 'i') {
        mediaManager->filterByType("2");
        currentPage = 1;
        this->nPages = ceil(mediaManager->getNMedia() / 8);
    }
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
