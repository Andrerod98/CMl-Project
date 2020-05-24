#ifndef Camera_screen_h
#define Camera_screen_h

#include <stdio.h>
#include "Screen.h"
#include "ofxDatGui.h"
#include "Camera.h"
#include "ofxOpenCv.h"
class CameraScreen : public Screen{
    void setup();

    
    ofxDatGuiLabel* gestures;
    ofxDatGuiLabel* people;
    ofxDatGuiLabel* nPeople;
    ofxDatGuiLabel* object;
    ofxDatGuiLabel* colorPat;
    ofxDatGuiLabel* audio;
    
    Camera* camera;
    
    
   
    
    
    
public:
    CameraScreen(string title,int width, int height,int x, int y,Camera* camera);
    
    void update();
    void keyPressed(int key);
    void mousePressed(int x, int y, int button);
    
    void draw();
    
};
#endif
