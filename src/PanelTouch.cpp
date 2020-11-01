#include "PanelTouch.h"
#include "PanelGUI.h" // To get screen boundaries

// 26,31,27,28,29
#define PIN_CLK 26
#define PIN_CS 31
#define PIN_DIN 27
#define PIN_DO 28
#define PIN_IRQ 29

PanelTouch::PanelTouch() 
    : URTouch(PIN_CLK, PIN_CS, PIN_DIN, PIN_DO, PIN_IRQ)
{

    InitTouch(LANDSCAPE);

}

XYCoords PanelTouch::getTouch(){
    
    XYCoords retCoords(0, 0);
    if(this->dataAvailable()){
        this->read();

        this->hasTouch = true;

        uint16_t x = this->getX();
        uint16_t y = this->getY();

        if(x <= SCREEN_WIDTH && y <= SCREEN_HEIGHT){
            retCoords.x = this->getX();
            retCoords.y = this->getY();

            this->prevTouch = retCoords;
        }
        else
            this->hasTouch = false;
    }
    else
        this->hasTouch = false;
    
    return retCoords;
}

