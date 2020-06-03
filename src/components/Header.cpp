#include "Header.h"

using namespace constants;

Header::Header(string title,int width, int height,int x, int y, vector<string> screens): Screen(title, width, height, x, y){
    
    this->screens = screens;
    this->currentScreen = 0;
    
    setFullHeader();
    isMetadata = false;
    
    setup();
}

void Header::setup(){
    title.load("fonts/Roboto-Medium.ttf", 16);
}

void Header::drawTabs() {
    //external container
    int containerHeight = getHeight();
    int containerWidth = getWidth()*0.4;
    
   /* ofSetColor(0);
    ofFill();
    ofDrawRectangle(getX(), getY(), containerWidth, containerHeight);
    */
    //navigtion options
    ofNoFill();
    
    int i = 1;
    int a = 0;
    for (string screenTitle : screens) {
        ofSetColor(FONT_COLOR);
    
        
        title.drawString(screenTitle, (containerWidth /(screens.size()*2)) * i - (title.stringWidth(screenTitle) / 2), (containerHeight* 0.75 - title.stringHeight(screenTitle) * 0.5));
        
        if(a == currentScreen){
            ofSetColor(FONT_COLOR);
            ofDrawLine((containerWidth /(screens.size()*2)) * i - (title.stringWidth(screenTitle) / 2), (containerHeight* 0.75 - title.stringHeight(screenTitle) * 0.5) + 10, (containerWidth /(screens.size()*2)) * i - (title.stringWidth(screenTitle) / 2) + title.stringWidth(screenTitle) , (containerHeight* 0.75 - title.stringHeight(screenTitle) * 0.5) + 10);
        }
        
       
        
        //divisor line
        ofSetColor(255);
        ofDrawLine((containerWidth /(screens.size()*2)) * (i+1), containerHeight * 0.4, (containerWidth /(screens.size()*2)) * (i+1), containerHeight * 0.8);
        i+=2;
        a++;
    }
    
     ofSetColor(255);
   
    
    
}

void Header::draw(){
    ofFill();
    ofSetColor(MAIN_COLOR); // fill color
    ofDrawRectangle(0, 0, ofGetWindowWidth(), getHeight());
    
    if(isMetadata)
        drawMetadataHeader();
    else
        drawFullHeader();
    
    ofFill();
    ofSetColor(255);
    
}

void Header::update(){
    liveButton->update();
    configButton->update();
    helpButton->update();
    refreshMetadata->update();
}

void Header::drawFullHeader(){
    liveButton->draw();
    configButton->draw();
    helpButton->draw();
    refreshMetadata->draw();
    
    drawTabs();
}

void Header::setHeader(Media* media){
    if(isMetadata)
        setMetadataHeader(media);
    else
        setFullHeader();
}
void Header::setFullHeader(){
    ofxDatGuiTheme* theme = new ofxDatGuiTheme();
    theme->init();
    
    
    theme->font.size = 10;
    theme->layout.height = 40;
    theme->font.ptr = ofxSmartFont::add(theme->font.file, theme->font.size);
    
    liveButton = new ofxDatGuiButton("Live");
    liveButton->setTheme(theme);
    liveButton->setPosition(getWidth()-120, 40-15);
    liveButton->setWidth(50, 100);
    liveButton->setLabelUpperCase(false);
    
    
    ofColor color(0, 0, 0);
    
    liveButton->setStripeColor(ofColor::red);
    //liveButton->setBorder(settings::FONT_COLOR, 1);
    liveButton->setBackgroundColor(SECONDARY_COLOR);
    liveButton->setLabelColor(ofColor::red);
    liveButton->onButtonEvent(this, &Header::liveButtonPress);
    
    configButton = new ofxDatGuiButton("Metadata");
    configButton->setTheme(theme);
    configButton->setPosition(getWidth()-220, 40-15);
    configButton->setWidth(80, 10);
    configButton->setLabelUpperCase(false);
    configButton->onButtonEvent(this, &Header::configButtonPress);
    configButton->setBackgroundColor(SECONDARY_COLOR);
    configButton->setLabelColor(FONT_COLOR);
    
    
    helpButton = new ofxDatGuiButton("Help");
    helpButton->setTheme(theme);
    helpButton->setPosition(getWidth()-310, 40-15);
    helpButton->setWidth(70, 10);
    helpButton->setLabelUpperCase(false);
    helpButton->onButtonEvent(this, &Header::helpButtonPress);
    helpButton->setBackgroundColor(SECONDARY_COLOR);
    helpButton->setLabelColor(FONT_COLOR);
    
	/*
    refreshMetadata = new ofxDatGuiButton("Refresh Metadata");
    refreshMetadata->setTheme(theme);
    refreshMetadata->setPosition(getWidth()-485, 40-15);
    refreshMetadata->setWidth(150, 10);
    refreshMetadata->setLabelUpperCase(false);
	refreshMetadata->onButtonEvent(this, &Header::refreshButtonPress);
    refreshMetadata->setBackgroundColor(settings::SECONDARY_COLOR);
    refreshMetadata->setLabelColor(settings::FONT_COLOR);
	*/

	refreshMetadata = new ofxDatGuiFolder("Refresh Metadata");
	refreshMetadata->setTheme(theme);
	refreshMetadata->setPosition(getWidth() - 485, 40 - 15);
	refreshMetadata->setWidth(150, 10);
	refreshMetadata->setLabelUpperCase(false);
	refreshMetadata->setBackgroundColor(MAIN_COLOR);
	refreshMetadata->setLabelColor(FONT_COLOR);
	refreshMetadata->addButton("Soft Reset");
	refreshMetadata->addButton("Hard Reset");
	refreshMetadata->onButtonEvent(this, &Header::refreshButtonPress);
    
    isMetadata = false;
}

void Header::drawMetadataHeader(){
    //liveButton->draw();
    //helpButton->draw();
    //refreshMetadata->draw();
    
    ofSetColor(255);
    title.drawString(this->media->getFileName(), 80, getHeight() / 2 + 5);
    backButton.draw(20,getHeight() / 2 - 10, 25, 25);
}
void Header::drawSelected(int selected){
    
}
void Header::setMetadataHeader( Media* media){
    ofxDatGuiTheme* theme = new ofxDatGuiTheme();
    theme->init();
    
    theme->font.size = 10;
    theme->layout.height = 40;
    theme->font.ptr = ofxSmartFont::add(theme->font.file, theme->font.size);
    
    liveButton = new ofxDatGuiButton("Live");
    liveButton->setTheme(theme);
    liveButton->setPosition(getWidth()-120, 40-15);
    liveButton->setWidth(50, 100);
    liveButton->setLabelUpperCase(false);
    
    ofColor color(0, 0, 0);
    liveButton->setBackgroundColor(SECONDARY_COLOR);
    liveButton->setStripeColor(ofColor::red);
    
    helpButton = new ofxDatGuiButton("Help");
    helpButton->setTheme(theme);
    helpButton->setPosition(getWidth()-210, 40-15);
    helpButton->setWidth(70, 10);
    helpButton->setLabelUpperCase(false);
    
    refreshMetadata = new ofxDatGuiFolder("Refresh Metadata");
    refreshMetadata->setTheme(theme);
    refreshMetadata->setPosition(getWidth()-380, 40-15);
    refreshMetadata->setWidth(150, 10);
    refreshMetadata->setLabelUpperCase(false);
    
    backButton.load("icons/back.png");
    this->media = media;
    
    isMetadata = true;
}

void Header::liveButtonPress(ofxDatGuiButtonEvent e){
    notifyObservers(Event::LIVE_BUTTON_PRESS);
}
void Header::configButtonPress(ofxDatGuiButtonEvent e){
    notifyObservers(Event::METADATA_BUTTON_PRESS);
}
void Header::helpButtonPress(ofxDatGuiButtonEvent e){
    notifyObservers(Event::HELP_BUTTON_PRESS);
}
void Header::darkButtonPress(ofxDatGuiButtonEvent e){
    notifyObservers(Event::GALLERY_TAB_CHANGE);
}
void Header::registerObserver(Observer *observer) {
    observers.push_back(observer);
}
void Header::refreshButtonPress(ofxDatGuiButtonEvent e) {
	MediaManager* mediaManager = mediaManager->getInstance();
	cout << "Refresh name: " << e.target->getName() << endl;
	if (e.target->getName() == "Soft Reset") 
		mediaManager->reloadNotify(true);
	else if (e.target->getName() == "Hard Reset") 
		mediaManager->reloadNotify(false);
}

void Header::removeObserver(Observer *observer) {
    // find the observer
    auto iterator = std::find(observers.begin(), observers.end(), observer);
    
    if (iterator != observers.end()) { // observer found
        observers.erase(iterator); // remove the observer
    }
}

void Header::notifyObservers(Event event) {

    for (Observer *observer : observers) { // notify all observers
      
        observer->update(event);
    }
}
void Header::keyPressed(int key) {
    if (key == 'g') {
        notifyObservers(Event::GALLERY_TAB_CHANGE);
        currentScreen = 0;
    }else if(key == 'c') {
        currentScreen = 1;
        notifyObservers(Event::CAMERA_TAB_CHANGE);
    }else if(key == 'l') {
    
        notifyObservers(Event::LIVE_BUTTON_PRESS);
    }else if(key == 'm') {

        notifyObservers(Event::METADATA_BUTTON_PRESS);
    }else if(key == 'h') {

        notifyObservers(Event::HELP_BUTTON_PRESS);
    }
}
//TODO
void Header::mousePressed(int x, int y, int button) {
    
    if(isMetadata){
        int xMin = 0 ;
        int xMax = 20 + 25 + 20;
        int yMin = 0;
        int yMax = getY()+ getHeight();
        
        if (x >= xMin && x <= xMax && y >= yMin && y <= yMax) {

            notifyObservers(Event::BACK_BUTTON_PRESS);
            
        }
    }else{
    int i = 1;
 
 
    for (string screenTitle : screens) {
        
       
        
        int xMin = (getWidth()*0.4 /(screens.size())) * (i-1);
        int xMax = (getWidth()*0.4 /(screens.size())) * (i);
        int yMin = getY();
        int yMax = getY()+ getHeight();
  
        
      
       
        if (x >= xMin && x <= xMax && y >= yMin && y <= yMax) {
            currentScreen = i-1;
       
            if(currentScreen == 0)
                notifyObservers(Event::GALLERY_TAB_CHANGE);
            else
                notifyObservers(Event::CAMERA_TAB_CHANGE);
            
        }
         i++;
    }
    }
}
