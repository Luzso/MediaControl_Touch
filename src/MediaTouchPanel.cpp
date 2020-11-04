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