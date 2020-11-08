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

enum activepanel {
    calibration,
    mediaplayer
} panel;


void startCalibration();
void startMediaPlayer();

void setup(){
    touch = new PanelTouch();
    delay(100);
    gui = new PanelGUI();

    
    startupanimation::animateStartup(gui);
    //startCalibration();
    //startMediaPlayer();

    delay(100);
}

void loop(){
    
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

