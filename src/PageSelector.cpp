//
//  pageSelector.cpp
//  cml-project
//
//  Created by User on 30/03/2020.
//

#include "PageSelector.h"
#include "ofMain.h"

PageSelector::PageSelector(string title,int width, int height, Screen& screen, int nPages):Screen(title, width, height){
    this->screen = &screen;
    this->nPages= nPages;
    
    currentPage = 1; //starts at 1
    
 
}

void PageSelector::drawSelected(int selected){
    
    ofSetColor(150);
    ofFill();
    
    if (currentPage == 1 && nPages > 1) {
        ofDrawTriangle(975, 450, 950, 425, 950, 475);
    }
    else if (currentPage > 1 && nPages > currentPage) {
        ofDrawTriangle(25, 450, 50, 425, 50, 475);
        ofDrawTriangle(975, 450, 950, 425, 950, 475);
    }
    else if (currentPage == nPages) {
        ofDrawTriangle(25, 450, 50, 425, 50, 475);
    }
    
    screen->drawSelected(currentPage);
}
void PageSelector::draw(){
    drawSelected(currentPage);
}



void PageSelector::nextPage(){
    currentPage = currentPage < nPages ? currentPage+=1 : currentPage;

}

void PageSelector::previousPage(){
    currentPage = currentPage != 1 ? currentPage-=1 : currentPage;
}

void PageSelector::update(){
    screen->update();
}

void PageSelector::setup(){
   
}

void PageSelector::mousePressed(int x, int y, int button) {
    screen->mousePressed(x, y, button);
    
    if (x >= 25 && x <= 50 && y >= 425 && y <= 475) {
       previousPage();
    }else if (x >= 950 && x <= 975 && y >= 425 && y <= 475) {
       nextPage();
    }
}
