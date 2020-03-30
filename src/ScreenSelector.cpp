#include "ScreenSelector.h"

ScreenSelector::ScreenSelector(string title,int width, int height, vector<Screen*> screens): Screen(title, width, height){
    
    this->screens = screens;
    this->currentScreen = 0;
}

void ScreenSelector::setup(){
    title.load("fonts/Roboto-Medium.ttf", 20);
}

void ScreenSelector::drawSelected(int selected) {
    //external container
    int containerHeight = 100;
    int containerWidth = 1000;
    
    ofSetColor(240);
    ofFill();
    ofDrawRectangle(0, 0, containerWidth, containerHeight);
    
    //navigtion options
    ofNoFill();
    
    int i = 1;
    for (Screen* element : screens) {
        ofSetColor(0);
        
        title.drawString(element->getTitle(), (ofGetWindowWidth() /(screens.size()*2)) * i - (title.stringWidth(element->getTitle()) / 2), (containerHeight* 0.75 - title.stringHeight(element->getTitle()) * 0.5));
        
        ofSetColor(200);
        
        //divisor line
        ofSetColor(150);
        ofDrawLine((ofGetWindowWidth() /(screens.size()*2)) * (i+1), containerHeight * 0.25, (ofGetWindowWidth() /(screens.size()*2)) * (i+1), containerHeight * 0.75);
        i+=2;
    }
    
    screens[currentScreen]->draw();
    
    
}

void ScreenSelector::draw(){
    drawSelected(currentScreen);
}

void ScreenSelector::update(){
    screens[currentScreen]->update();
}

void ScreenSelector::mousePressed(int x, int y, int button) {
    
    int i = 0;
    int xMin = 0;
    for (Screen* element : screens) {
        
        element->mousePressed(x, y, button);
        
        int xMax = (ofGetWindowWidth() /(screens.size())) * (i+1);
        
        if (x >= xMin && x <= xMax && y >= 25 && y <= 75) {
            currentScreen = i;
            
        }
        xMin = xMax;
        i++;
    }

}
