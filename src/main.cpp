#include <Arduino.h>
//#include "PanelGUI.h"
#include "CalibrationPanel.h"


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
            //calibrationPanel->update();
            break;

        default:
            break;
    }
    
}

void startCalibration(){
    panel = calibration;

    calibrationPanel = new CalibrationPanel(landscape);
    calibrationPanel->startCalibration();
}

