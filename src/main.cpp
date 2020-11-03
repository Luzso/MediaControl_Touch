#include <Arduino.h>
//#include "PanelGUI.h"
#include "CalibrationPanel.h"


URTouch* touch = NULL; // Is Initialized in class PanelTouch
PanelGUI* mediaPlayer;
CalibrationPanel* calibrationPanel;

enum activepanel {
    calibration,
    mediaplayer
} panel;


void startCalibration();

void setup(){

    //mediaPlayer = new PanelGUI();
    startCalibration();
    
    delay(100);

}

void loop(){
  
    switch(panel){
        case calibration:
            calibrationPanel->update();
            break;

        default:
            break;
    }
    
}

void startCalibration(){
    panel = calibration;

    calibrationPanel = new CalibrationPanel(touch, landscape);
    calibrationPanel->startCalibration();
}

