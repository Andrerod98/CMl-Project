#ifndef Camera_screen_h
#define Camera_screen_h

#include <stdio.h>
#include "Screen.h"
#include "ofxDatGui.h"
class CameraScreen : public Screen{
    void setup();
    //Video capture
    ofVideoGrabber vidGrabber;
    int camWidth;
    int camHeight;
    
    ofTrueTypeFont font;
    
    ofxDatGuiLabel* gestures;
    ofxDatGuiLabel* people;
    ofxDatGuiLabel* nPeople;
    ofxDatGuiLabel* object;
    ofxDatGuiLabel* colorPat;
    ofxDatGuiLabel* audio;
public:
    CameraScreen(string title,int width, int height,int x, int y);
    
    void update();
    void keyPressed(int key);
    void mousePressed(int x, int y, int button);
    
    void draw();
    
};
#endif
