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
    
    theme->font.size = 10;
    theme->layout.height = 50;
    theme->font.ptr = ofxSmartFont::add(theme->font.file, theme->font.size);

    ofxDatGuiLabel* audioAmplitude;
    luminance = new ofxDatGuiLabel("Luminance:" + to_string((media->getMetadata())->getLuminanceValue()));
    
    luminance->setPosition(xInfo, yInfo);
    luminance->setTheme(theme);
    luminance->setWidth(end - xInfo, 10);
    luminance->setLabelUpperCase(false);
    
    /*
    Tags (keywords)
    Luminance
    Color - based on first moment
    Number of faces appearing in the image or video
    Edge distribution
    Texture characteristics (for images and only for one sample frame of the video)
    Number of times a specific object (input as an image) appears in the video frame
    */
    
    
    rythm = new ofxDatGuiLabel("Rythm:" + to_string((media->getMetadata())->getRhythmValue()));
    rythm->setPosition(xInfo, yInfo + 100);
    rythm->setTheme(theme);
    rythm->setWidth(end - xInfo, 60);
    rythm->setLabelUpperCase(false);
    
    //edgeDistribution = new ofxDatGuiLabel("Edge Distribution:" + to_string((media->getMetadata())->getEdgeDistribution()));
    //edgeDistribution->setPosition(xInfo, yInfo +  200);
    //edgeDistribution->setTheme(theme);
    //edgeDistribution->setWidth(end - xInfo, 210);
    //edgeDistribution->setLabelUpperCase(false);

	Metadata* metadata = media->getMetadata();
	vector<int> edges = media->getMetadata()->getEdgeDistribution();
	vector<string> options = vector<string>(5);
	options.at(0) = "Vertical: " + to_string(edges.at(0));
	options.at(1) = "Horizontal: " + to_string(edges.at(1));
	options.at(2) = "45 Degree: " + to_string(edges.at(2));
	options.at(3) = "135 Degree: " + to_string(edges.at(3));
	options.at(4) = "Non Directional: " + to_string(edges.at(4));
	edgeDistribution = new ofxDatGuiDropdown("Edge Distribution", options);
	edgeDistribution->setPosition(xInfo, yInfo + 300);
	edgeDistribution->setTheme(theme);
	edgeDistribution->setWidth(end - xInfo, 210);
	edgeDistribution->setLabelUpperCase(false);
    
    
    nFaces = new ofxDatGuiLabel("Nº Faces:" + to_string((media->getMetadata())->getFacesNumber()));
    nFaces->setPosition(xInfo, yInfo + 50);
    nFaces->setTheme(theme);
    nFaces->setWidth(end - xInfo, 110);
    nFaces->setLabelUpperCase(false);
    

    vector<string> options2 = {};
    
    MediaManager* mediaManager = mediaManager->getInstance();
    int s = mediaManager->getObjectsNames().size();
    for (int i = 0; i < s; i++) {
        
        if(media->getMetadata()->getObjects().size() > i){
        options2.push_back(mediaManager->getObjectsNames()[i] + ":" + to_string( media->getMetadata()->getObjects()[i]));
        }
    }

    nObject = new ofxDatGuiDropdown("Nº objects:", options2);
    nObject->setPosition(xInfo, yInfo + 250);
    nObject->setTheme(theme);
    nObject->setWidth(end - xInfo, 160);
    nObject->setLabelUpperCase(false);

    
    texture = new ofxDatGuiLabel("Texture:"+ to_string((media->getMetadata())->getTextureValue()));
    texture->setPosition(xInfo, yInfo+ 150);
    texture->setTheme(theme);
    texture->setWidth(end - xInfo, 260);
    texture->setLabelUpperCase(false);
    
    colorLabel = new ofxDatGuiLabel("Color: ("+ to_string((media->getMetadata())->getColorValue().r)
                                    + "," +to_string((media->getMetadata())->getColorValue().g)
                                    + "," +to_string((media->getMetadata())->getColorValue().b) + ")");
    colorLabel->setPosition(xInfo, yInfo+ 200);
    colorLabel->setTheme(theme);
    colorLabel->setWidth(end - xInfo, 260);
    colorLabel->setLabelUpperCase(false);

    
    
    theme->layout.height = 60;
    saveButton = new ofxDatGuiButton("Save");
    saveButton->setPosition(30 + getWidth()*0.7 + 10, getHeight() - 40);
    saveButton->setTheme(theme);
    saveButton->setLabelUpperCase(false);
    saveButton->setWidth(end - xInfo + 10);
    saveButton->setBorder(ofColor::white, 1);
    saveButton->setLabelAlignment(ofxDatGuiAlignment::CENTER);
    saveButton->setStripeWidth(0);
    
    saveButton->onButtonEvent(this, &MetadataScreen::onButtonEvent);
    
    theme->layout.height = 30;
    tagsLabel = new ofxDatGuiLabel("Tags");
    tagsLabel->setPosition(30, getHeight() - 40);
    tagsLabel->setTheme(theme);
    tagsLabel->setWidth(getWidth()*0.7, 260);
    tagsLabel->setLabelUpperCase(false);
    
    
    
    
    theme->layout.width = getWidth()*0.7;
    theme->layout.labelWidth = 2;
    theme->layout.breakHeight = 5;
   
    theme->font.size = 12;
  
    theme->font.ptr = ofxSmartFont::add(theme->font.file, theme->font.size);
    
    tags = new ofxDatGuiTextInput("tags", "#teste");
    
    tags->setPosition(30, getHeight() - 10);
    tags->setTheme(theme);
 
    tags->setText(this->media->getMetadata()->getTagsString());
    
    
    
    
   // tags->setStripe(ofColor::white, 50);
    //tags->onTextInputEvent(this, &MetadataScreen::onTextInputEvent);
    
    tags->setLabelUpperCase(false);
    
    playButton.load("icons/play.png");
    pauseButton.load("icons/pause.png");
    replayButton.load("icons/replay.png");
    
}
vector<string> MetadataScreen::split(const string& str, const string& delim)
{
    vector<string> tokens;
    size_t prev = 0, pos = 0;
    do
    {
        pos = str.find(delim, prev);
        if (pos == string::npos) pos = str.length();
        string token = str.substr(prev, pos-prev);
        if (!token.empty()) tokens.push_back(token);
        prev = pos + delim.length();
    }
    while (pos < str.length() && prev < str.length());
    return tokens;
}

void MetadataScreen::onButtonEvent(ofxDatGuiButtonEvent e)
{
    // text input events carry the text of the input field //
    cout << "Saving tags " << tags->getText() << endl;
 
    std::string delimiter = "#";
    
    if(tags->getText() == "")
        return;
    
    size_t pos = 0;
    std::string token;
    std::string s = tags->getText();
    
    vector<std::string> r = {};
    vector<std::string> l = split(s, delimiter);
    
    for(string a : l){
        cout << "Token:" << a << "\n";
        r.push_back("#"+a);
    }
    
    
    
    
    this->media->getMetadata()->setTags(r);
    XmlManager *xml = xml->getInstance();
    PlaylistManager *pm = pm->getInstance();
    bool sucess = xml->setTags(this->media->getFileName(), this->media->isImage(), r);
    if(sucess){
        for(string s: r)
            pm->addToPlaylist(s,media);
    }
    cout << sucess;
    
    
    

}

void MetadataScreen::drawPlayer(){
    ofColor TEST_COLOR(0,0,0, 100);
    ofSetColor(TEST_COLOR);
    ofFill();
    ofDrawRectangle(30,140 + getHeight()-120 - 50 - 70, getWidth()*0.7, 50);
    ofSetColor(ofColor::white);
    ofFill();
    replayButton.draw(80,140 + getHeight()-120 - 50 + 25 - 15 - 70, 30, 30);
    
    if((media->getVideo())->isPaused()){
        playButton.draw(40,140 + getHeight()-120 - 50 + 25 - 15 - 70, 30, 30);
    }else{
        pauseButton.draw(40,140 + getHeight()-120 - 50 + 25 - 15 - 70, 30,30);
    }
}

void MetadataScreen::draw(){
    
    int xInfo = getWidth()*0.7 + 30 + 20;
    int yInfo =140;
    
    int end = getWidth() - 20;
    
    
    luminance->draw();
    
    edgeDistribution->draw();
    
    nFaces->draw();
    
    nObject->draw();
    
	//if (!media->isImage())
		rythm->draw();
    
    texture->draw();
    
    colorLabel->draw();
    ofSetColor(media->getMetadata()->getColorValue());
    
    
    colorLabel->setPosition(xInfo, yInfo+ 250);
    ofDrawRectangle(end - 35, yInfo+ 265 - 50, 25, 25);
    
    ofSetColor(0,0,0);
    
    
    tagsLabel->draw();
    tags->draw();
    
    saveButton->draw();
    
    ofSetColor(255);
    if(media->isImage()){
        (media->getImage())->draw(30,140, getWidth()*0.7, getHeight()-120 - 70);
        
        
    }else if(media->isVideo()){
        ofSetHexColor(0xFFFFFF);
        (media->getVideo())->draw(30,140, getWidth()*0.7, getHeight()-120 - 50 - 50-20);
        
        drawPlayer();
    }
    
}

void MetadataScreen::update(){
    int xInfo = getWidth()*0.7 + 30 + 20;
    int yInfo =140;
    int end = getWidth() - 20;
    saveButton->setPosition(30 + getWidth()*0.7 + 10, getHeight() - 40);
    saveButton->setWidth(end - xInfo + 10);
    tags->setPosition(30, getHeight() - 10);
    tags->setWidth(getWidth()*0.7, 2);
    tagsLabel->setPosition(30, getHeight() - 40);
    tagsLabel->setWidth(getWidth()*0.7, 260);
    colorLabel->setPosition(xInfo, yInfo+ 200);
    colorLabel->setWidth(end - xInfo, 260);
    texture->setPosition(xInfo, yInfo+ 150);
    texture->setWidth(end - xInfo, 260);
    nObject->setPosition(xInfo, yInfo + 250);
    nObject->setWidth(end - xInfo, 160);
    nFaces->setPosition(xInfo, yInfo + 50);
    nFaces->setWidth(end - xInfo, 110);
    edgeDistribution->setPosition(xInfo, yInfo + 300);
    edgeDistribution->setWidth(end - xInfo, 210);
    rythm->setPosition(xInfo, yInfo + 100);
    rythm->setWidth(end - xInfo, 60);
    luminance->setPosition(xInfo, yInfo);
    luminance->setWidth(end - xInfo, 10);
    saveButton->update();
    tags->update();
	edgeDistribution->update();
	texture->update();
	colorLabel->update();
    nObject->update();
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
