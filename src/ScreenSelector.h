#include <stdio.h>
#include "ofMain.h"
#include "Screen.h"

using namespace std;

class ScreenSelector : public Screen{
public:
    ScreenSelector(string title,int width, int height, vector<Screen*> screens);
    
    void setup();
    void drawSelected(int selected);
    void draw();
    void update();
 
    void mousePressed(int x, int y, int button);
    
    
    int currentScreen;
    
    int nScreens;
    
    vector<Screen*> screens;
    
    ofTrueTypeFont title;

};
