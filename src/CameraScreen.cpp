//
//  cameraScreen.cpp
//  cml-project
//
//  Created by User on 30/03/2020.
//

#include "CameraScreen.h"

CameraScreen::CameraScreen(string title,int width, int height):Screen(title, width, height){
    
}


void CameraScreen::setup(){
    
    // try to grab at this size
    camWidth = getWidth();
    camHeight = getHeight();
    
    vidGrabber.setVerbose(true);
    vidGrabber.setup(camWidth,camHeight);
    
    font.load("fonts/Roboto-Medium.ttf", 9);
    
    // this set of characters comes from the Ascii Video Processing example by Ben Fry,
    // changed order slightly to work better for mapping
    asciiCharacters =  string("  ..,,,'''``--_:;^^**""=+<>iv%&xclrs)/){}I?!][1taeo7zjLunT#@JCwfy325Fp6mqSghVd4EgXPGZbYkOA8U$KHDBWNMR0Q");
    
    ofEnableAlphaBlending();
}


//--------------------------------------------------------------
void CameraScreen::update(){
    vidGrabber.update();
}

//--------------------------------------------------------------
void CameraScreen::draw(){

    // change background video alpha value based on the cursor's x-position
    float videoAlphaValue = ofMap(ofGetAppPtr()->mouseX, 0, ofGetWidth(), 0, 255);
    
    // set a white fill color with the alpha generated above
    ofSetColor(255,255,255,videoAlphaValue);
    
    // draw the raw video frame with the alpha value generated above
    vidGrabber.draw(0,100);
    
    ofPixelsRef pixelsRef = vidGrabber.getPixels();
    
    ofSetHexColor(0xffffff);
    
    for (int i = 0; i < camWidth; i+= 7){
        for (int j = 0; j < camHeight; j+= 9){
            // get the pixel and its lightness (lightness is the average of its RGB values)
            float lightness = pixelsRef.getColor(i,j).getLightness();
            
            // calculate the index of the character from our asciiCharacters array
            int character = powf( ofMap(lightness, 0, 255, 0, 1), 2.5) * asciiCharacters.size();
            
            // draw the character at the correct location
            font.drawString(ofToString(asciiCharacters[character]), i, j);
        }
    }
    
}


//--------------------------------------------------------------
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


void CameraScreen::drawSelected(int selected) {
    
}


