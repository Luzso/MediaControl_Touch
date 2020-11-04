#include "Button.h"

Button::Button(void(*btnCallback)(), int x, int y, int width, int height){

    this->setBtnCallback(btnCallback);
    this->setPosition(x, y);
    this->setDimensions(width, height);
    // setGraphics();
}

void Button::pressed(){
    if(this->btnPressCallback != nullptr){
        this->btnPressCallback();
    }
}

void Button::setBtnCallback(void(*btnCallback)()){
    btnPressCallback = btnCallback;
}

void Button::setPosition(int xPos, int yPos){
    this->x = xPos;
    this->y = yPos;
}

void Button::setDimensions(int width, int height){
    this->touchWidth = width;
    this->touchHeight = height;
}