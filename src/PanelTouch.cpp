#include "PanelTouch.h"
#include "PanelGUI.h" // To get screen boundaries

// 26,31,27,28,29
#define PIN_CLK 26
#define PIN_CS 31
#define PIN_DIN 27
#define PIN_DO 28
#define PIN_IRQ 29

PanelTouch::PanelTouch(URTouch* touchObj)
{
    this->setTouchObj(touchObj);

    this->init();
}

void PanelTouch::setTouchObj(URTouch* touchObj){
    this->touch = touchObj;
}

void PanelTouch::init(){
    this->touch = new URTouch(PIN_CLK, PIN_CS, PIN_DIN, PIN_DO, PIN_IRQ);
    this->touch->InitTouch(LANDSCAPE);
}

XYCoords PanelTouch::getTouch(){
    
    XYCoords retCoords(0, 0);
    if(this->touch->dataAvailable()){
        if(this->isReadyForNewTouch()){
            // Read the available coordinates
            this->touch->read();
            uint16_t x = this->touch->getX();
            uint16_t y = this->touch->getY();

            if(true || x <= SCREEN_WIDTH && y <= SCREEN_HEIGHT){
                retCoords.x = this->touch->getX();// * 1.48;
                retCoords.y = this->touch->getY();// * 1.333;
                this->setHasTouch(true);
            }
            else
                this->setHasTouch(false);
        }
        else
            this->hasTouch = false;
        
    }
    else{
        if(this->hasTouch) // Touch was registered at last update, meaning finger has just been lifted
            this->timeAtLift = millis(); // Update timestamp of lifted finger. 

        this->setHasTouch(false);
    }
    
    this->prevTouch = retCoords;
    return retCoords;
}

bool PanelTouch::isReadyForNewTouch(){

    // Check if the finger was lifted due to uncertainty of the touch panel or if it seems intentional (Time since lift)
    unsigned long timeSinceLift = millis() - this->timeAtLift; // Check how long it is since a lift was registered
    
    if(!this->hasTouch && timeSinceLift > this->liftTimeout)
        return true;
    
    this->timeAtLift = millis();
    return false;
}


void PanelTouch::setHasTouch(bool touchActive){
    this->hasTouch = touchActive;
}

XYCoords PanelTouch::getTouchDown(){
    XYCoords tempCoords = this->getTouch();
    while(this->touch->dataAvailable())
    return tempCoords;
}