#include "MediaTouchGUI.h"


void drawStartStopDS(PanelGUI* guiObj, int xCenter, int yCenter){
    int circRadius = 25;
    guiObj->clearRect(xCenter - circRadius, yCenter - circRadius, 2*circRadius, 2*circRadius);
    guiObj->monitor->drawCircle(xCenter, yCenter, circRadius, ILI9488_WHITE);

}


void drawStartStopS(PanelGUI* guiObj, int xCenter, int yCenter){
    guiObj->monitor->fillCircle(xCenter, yCenter, 25, ILI9488_WHITE);
}
