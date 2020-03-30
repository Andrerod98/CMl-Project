//
//  cameraScreen.hpp
//  cml-project
//
//  Created by User on 30/03/2020.
//

#include <stdio.h>
#include "ofMain.h"
#include "Screen.h"
class CameraScreen : public Screen{
public:
    CameraScreen(string title,int width, int height);
    void setup();
    void update();
    void keyPressed(int key);
    void drawSelected(int selected);
    void mousePressed(int x, int y, int button);
    void draw();
    
    
    //Video capture
    ofVideoGrabber vidGrabber;
    int camWidth;
    int camHeight;
    
    string asciiCharacters;
    ofTrueTypeFont font;


};
