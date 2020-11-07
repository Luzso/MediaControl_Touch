#include "BasePanel.h"

BasePanel::BasePanel(PanelTouch* touch, PanelGUI* gui) 
{
    this->touchObj = touch;
    this->guiObj = gui;
}

// MOVE TO BASE PANEL
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
    else if(this->touchObj->getRelease()){ // True if button was just released
    for(int i_btn = 0; i_btn < this->nButtons; i_btn++)
        buttons[i_btn].deSelect();
    }
    
}

