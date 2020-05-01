//
//  cameraScreen.cpp
//  cml-project
//
//  Created by User on 30/03/2020.
//

#include "CameraScreen.h"

CameraScreen::CameraScreen(string title,int width, int height,int x, int y):Screen(title, width, height,x,y){
    
    
    setup();
}

void CameraScreen::setup(){
    
    // try to grab at this size
    camWidth = getWidth() * 0.8;
    camHeight = getHeight()-50;
    camWidth = 1024;
    camHeight = 768;
    
    vidGrabber.setVerbose(true);
    vidGrabber.setup(camWidth,camHeight);
    
    font.load("fonts/Roboto-Medium.ttf", 9);
    
    ofEnableAlphaBlending();
    
    int xInfo = getWidth()*0.7 + 30 + 20;
    int yInfo =140;
    
    int end = getWidth() - 20;
    
    ofxDatGuiTheme* theme = new ofxDatGuiTheme();
    theme->init();
    
    
    theme->font.size = 14;
    theme->layout.height = 50;
    theme->font.ptr = ofxSmartFont::add(theme->font.file, theme->font.size);
    gestures = new ofxDatGuiLabel("Luminance");
    
    gestures->setPosition(xInfo, yInfo);
    gestures->setTheme(theme);
    gestures->setWidth(end - xInfo, 10);
    gestures->setLabelUpperCase(false);

    
    people = new ofxDatGuiLabel("People");
    people->setPosition(xInfo, yInfo + 50);
    people->setTheme(theme);
    people->setWidth(end - xInfo, 60);
    people->setLabelUpperCase(false);

    
    nPeople = new ofxDatGuiLabel("Nº People");
    nPeople->setPosition(xInfo, yInfo + 100);
    nPeople->setTheme(theme);
    nPeople->setWidth(end - xInfo, 110);
    nPeople->setLabelUpperCase(false);
  
    
    object = new ofxDatGuiLabel("Object");
    object->setPosition(xInfo, yInfo + 150);
    object->setTheme(theme);
    object->setWidth(end - xInfo, 160);
    object->setLabelUpperCase(false);

    
    colorPat = new ofxDatGuiLabel("Color pattern");
    colorPat->setPosition(xInfo, yInfo +  200);
    colorPat->setTheme(theme);
    colorPat->setWidth(end - xInfo, 210);
    colorPat->setLabelUpperCase(false);

    
    audio = new ofxDatGuiLabel("Audio");
    audio->setPosition(xInfo, yInfo+ 250);
    audio->setTheme(theme);
    audio->setWidth(end - xInfo, 260);
    audio->setLabelUpperCase(false);

}

void CameraScreen::draw(){
    
    // change background video alpha value based on the cursor's x-position
    float videoAlphaValue = ofMap(ofGetAppPtr()->mouseX, 0, ofGetWidth(), 0, 255);
    
    // set a white fill color with the alpha generated above
    ofSetColor(255,255,255,videoAlphaValue);
    
    // draw the raw video frame with the alpha value generated above
    vidGrabber.draw(30,140, getWidth()*0.7, getHeight()-120);
    
    ofPixelsRef pixelsRef = vidGrabber.getPixels();
    
    ofSetHexColor(0xffffff);

    gestures->draw();
    people->draw();
    nPeople->draw();
    object->draw();
    colorPat->draw();
    audio->draw();
    
}

void CameraScreen::update(){
    vidGrabber.update();
}

void CameraScreen::keyPressed  (int key){
    
    // in fullscreen mode, on a pc at least, the
    // first time video settings the come up
    // they come up *under* the fullscreen window
    // use alt-tab to navigate to the settings
    // window. we are working on a fix for this...
    
    if (key == 's' || key == 'S'){
        vidGrabber.videoSettings();
    }
    
}

void CameraScreen::mousePressed(int x, int y, int button) {
    
}



