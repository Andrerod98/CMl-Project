#include "Header.h"



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
        ofSetColor(255);
    
        
        title.drawString(screenTitle, (containerWidth /(screens.size()*2)) * i - (title.stringWidth(screenTitle) / 2), (containerHeight* 0.75 - title.stringHeight(screenTitle) * 0.5));
        
        if(a == currentScreen){
            ofSetColor(255);
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
    ofSetColor(settings::MAIN_COLOR); // fill color
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
    darkButton->update();
}

void Header::drawFullHeader(){
    liveButton->draw();
    configButton->draw();
    helpButton->draw();
    darkButton->draw();
    
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
    liveButton->setBackgroundColor(settings::SECONDARY_COLOR);
    liveButton->setStripeColor(ofColor::red);
    liveButton->onButtonEvent(this, &Header::liveButtonPress);
    
    configButton = new ofxDatGuiButton("Config");
    configButton->setTheme(theme);
    configButton->setPosition(getWidth()-210, 40-15);
    configButton->setWidth(70, 10);
    configButton->setLabelUpperCase(false);
    configButton->onButtonEvent(this, &Header::configButtonPress);
    
    
    helpButton = new ofxDatGuiButton("Help");
    helpButton->setTheme(theme);
    helpButton->setPosition(getWidth()-300, 40-15);
    helpButton->setWidth(70, 10);
    helpButton->setLabelUpperCase(false);
    helpButton->onButtonEvent(this, &Header::helpButtonPress);
    
    darkButton = new ofxDatGuiToggle("Dark mode");
    darkButton->setTheme(theme);
    darkButton->setPosition(getWidth()-425, 40-15);
    darkButton->setWidth(100, 10);
    darkButton->setLabelUpperCase(false);
    
    isMetadata = false;
}

void Header::drawMetadataHeader(){
    liveButton->draw();
    helpButton->draw();
    darkButton->draw();
    
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
    liveButton->setBackgroundColor(settings::SECONDARY_COLOR);
    liveButton->setStripeColor(ofColor::red);
    
    helpButton = new ofxDatGuiButton("Help");
    helpButton->setTheme(theme);
    helpButton->setPosition(getWidth()-210, 40-15);
    helpButton->setWidth(70, 10);
    helpButton->setLabelUpperCase(false);
    
    darkButton = new ofxDatGuiToggle("Dark mode");
    darkButton->setTheme(theme);
    darkButton->setPosition(getWidth()-330, 40-15);
    darkButton->setWidth(100, 10);
    darkButton->setLabelUpperCase(false);
    
    
    
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
