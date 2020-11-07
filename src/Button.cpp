#include "Button.h"

Button::Button(
    PanelGUI* gui,
    void(*btnCallback)(),
    void(*drawDeselected)(PanelGUI*, int, int), 
    void(*drawSelected)(PanelGUI*, int, int), 
    int xCenter, 
    int yCenter, 
    int width, 
    int height){

    this->guiObj = gui;

    this->setBtnCallback(btnCallback);
    this->setPosition(xCenter, yCenter);
    this->setDimensions(width, height);

    this->drawDS = drawDeselected;
    this->drawS = drawSelected;

    drawDS(this->guiObj, xCenter, yCenter);
}


bool Button::wasPressed(int xTouched, int yTouched){
    if(
        xTouched >= this->xCenter - touchWidth / 2 && xTouched <= this->xCenter + touchWidth / 2 &&
        yTouched >= this->yCenter - touchHeight / 2 && yTouched <= this->yCenter + touchHeight / 2 &&
        this->active)
        {
            this->selected = true;
            return true;
        }
    else
        return false;
}

void Button::press(){
    if(this->active){
        if(this->btnPressCallback != nullptr){
            this->btnPressCallback();
        }
        if(this->drawS != nullptr)
            this->drawS(this->guiObj, this->xCenter, this->yCenter);
    }
}

void Button::setBtnCallback(void(*btnCallback)()){
    btnPressCallback = btnCallback;
}

void Button::setPosition(int xPos, int yPos){
    this->xCenter = xPos;
    this->yCenter = yPos;
}

void Button::setDimensions(int width, int height){
    this->touchWidth = width;
    this->touchHeight = height;
}

void Button::deSelect(){
    if(this->active && this->selected){
        this->selected = false;
        this->drawDS(this->guiObj, xCenter, yCenter); 
    }
}