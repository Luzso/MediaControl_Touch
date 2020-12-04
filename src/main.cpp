#include <Arduino.h>
#include "MediaTouchPanel.h"
#include "CalibrationPanel.h"
#include "PanelTouch.h"
#include "PanelGUI.h"
#include "StartupAnimation.h"

PanelTouch* touch;
PanelGUI* gui;

MediaTouchPanel* mediaPlayerPanel = NULL;
CalibrationPanel* calibrationPanel;

bool firstRun = true;

enum activepanel {
    none,
    calibration,
    mediaplayer
} panel;


void startCalibration();
void startMediaPlayer();
void testBackgroundGraphics();

void setup(){
    Serial.begin(9600);
    touch = new PanelTouch();
    delay(100);
    gui = new PanelGUI();

    panel = none;

    //startupanimation::animateStartup(gui);
    //startCalibration();
    //startMediaPlayer();

    delay(100);
}

void loop(){
    
    
    
    if(touch->dataAvailable() && firstRun){
        testBackgroundGraphics();
        firstRun = false;
    }

    
    switch(panel){
        case calibration:
            calibrationPanel->update();
            break;

        case mediaplayer:
            mediaPlayerPanel->update();
            break;

        default:
            break;
    }

}

void startMediaPlayer(){
    panel = mediaplayer;

    mediaPlayerPanel = new MediaTouchPanel(touch, gui);
}

void startCalibration(){
    panel = calibration;

    calibrationPanel = new CalibrationPanel(touch, gui, portrait);
    calibrationPanel->startCalibration();
}

void testBackgroundGraphics(){
    Serial.println("Testing background bmp graphics");
    gui->drawBitmap(0, 0, "DEFAUL~1.BMP");
}