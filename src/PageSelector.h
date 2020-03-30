//
//  pageSelector.hpp
//  cml-project
//
//  Created by User on 30/03/2020.
//

#ifndef pageSelector_h
#define pageSelector_h

#include <stdio.h>

#include "Screen.h"

class PageSelector : public Screen{
public:
    PageSelector(string title,int width, int height, Screen& screen, int nPages);
    
    void setup();
    void drawSelected(int selected);
    void draw();
    void nextPage();
    void previousPage();
    void update();
    
    void mousePressed(int x, int y, int button);
    
    int currentPage;
    
    int nPages;
    
    Screen* screen;
    
    
};

#endif /* pageSelector_hpp */

