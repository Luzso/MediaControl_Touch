#include "Button.h"

// Initialize the button
// The button initialization includes
// - Setting the "pressed" callback function of the button, which 
//   will likely be located in the Panel class that the button was created in.
// - Setting the drawing callback functions that draws the button when it is being selected 
//   and when it is not selected.
// - xCenter and yCenter describes the center of the spawned button
// - width and height arguments are used as boundaries together with the center coordinates to detect 
//   if the given button was pressed on touch-detection.
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


// Check if this buttons was pressed when a touch was detected at the argument coordinates. 
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