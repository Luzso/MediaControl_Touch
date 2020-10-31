#include "CalibrationPanel.h"

CalibrationPanel::CalibrationPanel() 
    : BasePanel()
{
    textBackground.color = ILI9488_DARKGREY;
    textBackground.useDefaultBackground = false;
}


void CalibrationPanel::startCalibration(){
    this->initBackgroundVisuals();
        
}

void CalibrationPanel::update(){

    TouchCoords touch = this->getTouch();
    if(this->hasTouch){

        


        if(!touch.compare(&this->prevTouch))
            writeReadXY(&touch);
    }
    else{
        prevTouch.x++;
        prevTouch.y++;
        writeReadXY(&prevTouch);
    }
    delay(100); // Replace with timer check
}


void CalibrationPanel::initBackgroundVisuals(){
    this->clearScreen();
    this->setSaveFont(Arial_12);

    this->drawCrossHair(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);
    this->writeInBox_sizes("Calibrating.", SCREEN_WIDTH / 2 - 10, 0, 20, 10, true, TextboxBackground(), false);
    this->monitor->fillRect(0, SCREEN_HEIGHT - 30, 150, 30, textBackground.color);
    this->writeInBox_sizes("Coordinates: ", 1, SCREEN_HEIGHT - 20, 50, 10, false, textBackground, false);
}


void CalibrationPanel::writeReadXY(TouchCoords* xy){
    String xyString = String(xy->x) + ", " + String(xy->y);
    this->monitor->fillRect(100, SCREEN_HEIGHT - 30, 100, 30, textBackground.color);

    this->writeInBox_sizes(xyString, 100, SCREEN_HEIGHT - 20, 35, 10, false, this->textBackground, false);
}