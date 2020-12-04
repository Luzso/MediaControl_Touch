#include "BasePanel.h"


// Intialize the BasePanel class by saving pointers to the Touch panel's touch (detection) and gui (drawing) classes
BasePanel::BasePanel(PanelTouch* touch, PanelGUI* gui) 
{
    this->touchObj = touch;
    this->guiObj = gui;
}



// Catch any touches on the panel and check wether or not the touch coordinates is within one of the spawned button boundaries. 
void BasePanel::update(){

    XYCoords touchPoint = this->touchObj->getTouch();
    if(this->touchObj->hasTouch){
        for(int i_btn = 0; i_btn < this->nButtons; i_btn++){
            if(buttons[i_btn].wasPressed(touchPoint.x, touchPoint.y)){
                buttons[i_btn].press();
                break;
            }
            
        }
    }
    else if(this->touchObj->getRelease()){ // Check if a button has just been pressed and afterwards released to uncheck any selected buttons
    for(int i_btn = 0; i_btn < this->nButtons; i_btn++)
        buttons[i_btn].deSelect();
    }

}

