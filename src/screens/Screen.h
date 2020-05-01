#ifndef Screen_h
#define Screen_h
#include "ofMain.h"

#pragma once

class Screen {
    string title;
    int width, height;
    int x,y;
    
public:
    Screen(string title, int width, int height, int x, int y){
        this->title = title;
        this->width = width;
        this->height = height;
        this->x = x;
        this->y = y;
    };
    
    virtual void draw() = 0;
    virtual void mousePressed(int x, int y, int button) = 0;
    virtual void update() = 0;
    
    string getTitle(){
        return title;
    };
    
    int getWidth(){
        return width;
    }
    int getHeight(){
        return height;
    }
    void setWidth(int w){
        this->width = w;
    }
    void setHeight(int h){
        this->height = h;
    }
    
    int getX(){
        return x;
    }
    
    int getY(){
        return y;
    }
};

#endif
