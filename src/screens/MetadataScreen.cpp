//
//  MetadataScreen.cpp
//  CMl-Project
//
//  Created by User on 30/04/2020.
//

#include "MetadataScreen.h"

MetadataScreen::MetadataScreen(string title,int width, int height,int x, int y, MediaGUI* media):Screen(title, width, height,x,y){
    
    this->media = media;
    setup();
}

void MetadataScreen::setup(){
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
    
    
    theme->layout.height = 60;
    saveButton = new ofxDatGuiButton("Save");
    saveButton->setPosition(30 + getWidth()*0.7 + 10, getHeight() - 40);
    saveButton->setTheme(theme);
    saveButton->setLabelUpperCase(false);
    saveButton->setWidth(end - xInfo + 10);
    saveButton->setBorder(ofColor::white, 1);
    saveButton->setLabelAlignment(ofxDatGuiAlignment::CENTER);
    saveButton->setStripeWidth(0);
    
    theme->layout.height = 30;
    audio = new ofxDatGuiLabel("Tags");
    audio->setPosition(30, getHeight() - 40);
    audio->setTheme(theme);
    audio->setWidth(getWidth()*0.7, 260);
    audio->setLabelUpperCase(false);
    
    
    
    
    theme->layout.width = getWidth()*0.7;
    theme->layout.labelWidth = 2;
    theme->layout.breakHeight = 5;
   
    theme->font.size = 12;
  
    theme->font.ptr = ofxSmartFont::add(theme->font.file, theme->font.size);
    
    tags = new ofxDatGuiTextInput("tags", "#teste");
    
    tags->setPosition(30, getHeight() - 10);
    tags->setTheme(theme);
   
    
    
    
   // tags->setStripe(ofColor::white, 50);
    tags->onTextInputEvent(this, &MetadataScreen::onTextInputEvent);
    
    tags->setLabelUpperCase(false);
    
    playButton.load("icons/play.png");
    pauseButton.load("icons/pause.png");
    replayButton.load("icons/replay.png");
    
}

void MetadataScreen::onTextInputEvent(ofxDatGuiTextInputEvent e)
{
    // text input events carry the text of the input field //
    cout << "From Event Object: " << e.text << endl;
    // although you can also retrieve it from the event target //
    cout << "From Event Target: " << e.target->getText() << endl;
}

void MetadataScreen::drawPlayer(){
    ofColor TEST_COLOR(44,44,44);
    ofSetColor(TEST_COLOR);
    ofFill();
    ofDrawRectangle(30,140 + getHeight()-120 - 50 - 70, getWidth()*0.7, 50);
    
    replayButton.draw(80,140 + getHeight()-120 - 50 + 25 - 15 - 70, 30, 30);
    
    if((media->getVideo())->isPaused()){
        playButton.draw(40,140 + getHeight()-120 - 50 + 25 - 15 - 70, 30, 30);
    }else{
        pauseButton.draw(40,140 + getHeight()-120 - 50 + 25 - 15 - 70, 30,30);
    }
}

void MetadataScreen::draw(){
    
    
    ofSetColor(255);
    if(media->isImage()){
        (media->getImage())->draw(30,140, getWidth()*0.7, getHeight()-120 - 70);
        
        
    }else if(media->isVideo()){
        ofSetHexColor(0xFFFFFF);
        (media->getVideo())->draw(30,140, getWidth()*0.7, getHeight()-120 - 50 - 50);
        
        drawPlayer();
    }
   
    gestures->draw();
    
    people->draw();
    
    nPeople->draw();
    
    object->draw();
    
    colorPat->draw();
    
    audio->draw();
    
    tags->draw();
    
    saveButton->draw();
    
}

void MetadataScreen::update(){
    saveButton->update();
    tags->update();
    if(media->isVideo()){
        (media->getVideo())->update();
    }
    
    
}

void MetadataScreen::mousePressed(int x, int y, int button){
    int playButtonX = 40;
    int playButtonY = 140 + getHeight()-120 - 50 + 25 - 15 - 70;
  
    if(media->isVideo()){
        //Play and pause
        if (x >= playButtonX && x <= playButtonX + 30 && y >= playButtonY && y <= playButtonY+30) {
            if((media->getVideo())->isPaused()){
                (media->getVideo())->play();
            }else{
                (media->getVideo())->setPaused(true);
            }
        }else if (x >= playButtonX + 40 && x <= playButtonX  + 40 + 30 && y >= playButtonY && y <= playButtonY+30){
            (media->getVideo())->stop();
        }
    }
    
}
