#include "ofMain.h"

class Screen {
public:
    
    explicit Screen(string title, int width, int height){
        this->title = title;
        this->width = width;
        this->height = height;
    }
    
    virtual void drawSelected(int selected) = 0;
    virtual void draw() = 0;
    virtual void mousePressed(int x, int y, int button) = 0;
    virtual void setup() = 0;
    virtual void update() = 0;
    
    
    vector<ofVec2f> positions;
    
    string getTitle(){
        return title;
    };
    
    int getWidth(){
        return width;
    }
    
    int getHeight(){
        return height;
    }
private:
    string title;
    int width, height;
};

