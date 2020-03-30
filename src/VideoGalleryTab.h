
#include <stdio.h>
#include "ofMain.h"
#include "Screen.h"

class VideoGalleryTab : public Screen{
public:
    VideoGalleryTab(string title,int width, int height);
    

    void load();
    void drawSelected(int selected);
    void draw();
    void update();
    void mousePressed(int x, int y, int button);
    void setup();
    
    
    ofDirectory diretory;
    vector<ofVideoPlayer> videos;
    
    int currentVideo;
private:
    void createPositions();
    
    vector<ofVec2f> positions;
};

