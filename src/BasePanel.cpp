#include "BasePanel.h"

BasePanel::BasePanel(URTouch* touchObj) 
    : PanelTouch(touchObj), PanelGUI()
{
    // Recall calibration from FLASH
}


void BasePanel::performTouchCalibration(){

}