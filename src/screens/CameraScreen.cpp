//
//  cameraScreen.cpp
//  cml-project
//
//  Created by User on 30/03/2020.
//

#include "CameraScreen.h"

CameraScreen::CameraScreen(string title,int width, int height,int x, int y, Camera* camera):Screen(title, width, height,x,y){
    
    this->camera = camera;//new CameraUtils();
    setup();
}

void CameraScreen::setup(){


    
    

    
    
    
    
    int xInfo = getWidth()*0.7 + 30 + 20;
    int yInfo =140;
    
    int end = getWidth() - 20;
    
    ofxDatGuiTheme* theme = new ofxDatGuiTheme();
    theme->init();
    
    
    theme->font.size = 10;
    theme->layout.height = 50;
    theme->font.ptr = ofxSmartFont::add(theme->font.file, theme->font.size);
    
    
    
    
    
    
    ofxDatGuiLabel* audioAmplitude;
    
    int nPeople = this->camera->getNPeople();
    string anywoneWatchingLabel = nPeople > 0 ? "Yes": "No";
    anywoneWatching = new ofxDatGuiLabel("Is anywone watching:" + anywoneWatchingLabel);
    
    anywoneWatching->setPosition(xInfo, yInfo);
    anywoneWatching->setTheme(theme);
    anywoneWatching->setWidth(end - xInfo, 10);
    anywoneWatching->setLabelUpperCase(false);
    
    
    nPeopleWatching = new ofxDatGuiLabel("Nº of people watching:" + to_string(nPeople));
    nPeopleWatching->setPosition(xInfo, yInfo + 50);
    nPeopleWatching->setTheme(theme);
    nPeopleWatching->setWidth(end - xInfo, 60);
    nPeopleWatching->setLabelUpperCase(false);
    
    gestures = new ofxDatGuiLabel("Gestures: Not implemented");
    gestures->setPosition(xInfo, yInfo +  150);
    gestures->setTheme(theme);
    gestures->setWidth(end - xInfo, 210);
    gestures->setLabelUpperCase(false);
    
    
    sound = new ofxDatGuiLabel("Sound: Not implemented" );
    sound->setPosition(xInfo, yInfo + 100);
    sound->setTheme(theme);
    sound->setWidth(end - xInfo, 110);
    sound->setLabelUpperCase(false);
    
    
    


}

void CameraScreen::draw(){
    

    
    // draw the raw video frame with the alpha value generated above
    camera->getVideoGrabber().draw(30,140, getWidth()*0.7, getHeight()-120);
   

    gestures->draw();
    sound->draw();
    anywoneWatching->draw();
    nPeopleWatching->draw();
    
}



void CameraScreen::update(){
    
    
    camera->update();
    int nPeople = this->camera->getNPeople();
    string anywoneWatchingLabel = nPeople > 0 ? "Yes": "No";
    nPeopleWatching->setLabel("Nº of people watching:" + to_string(nPeople));
    anywoneWatching->setLabel("Is anywone watching:" + anywoneWatchingLabel);
}

void CameraScreen::keyPressed  (int key){
    
    // in fullscreen mode, on a pc at least, the
    // first time video settings the come up
    // they come up *under* the fullscreen window
    // use alt-tab to navigate to the settings
    // window. we are working on a fix for this...
    
    if (key == 's' || key == 'S'){
        camera->getVideoGrabber().videoSettings();
    }
    
}

void CameraScreen::mousePressed(int x, int y, int button) {
    
}



