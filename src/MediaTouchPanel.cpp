#include "MediaTouchPanel.h"

MediaTouchPanel::MediaTouchPanel(URTouch* touchObj) 
    : BasePanel(touchObj)
{

}

void MediaTouchPanel::drawMainUI(){

}

void MediaTouchPanel::update(){

    XYCoords touch = this->getTouch();
    if(this->hasTouch){
        // Do something
    }
    
}

void MediaTouchPanel::createButtons(){
    this->nButtons = 1;
    this->buttons = new Button[nButtons];
    this->addButton("PlayPause", &onBtn_startPause, SCREEN_WIDTH/2, SCREEN_HEIGHT/2, 50, 50);
}


void MediaTouchPanel::onBtn_startPause(){

}