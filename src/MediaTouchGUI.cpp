#include "MediaTouchGUI.h"


void drawStartStopDeSelected(PanelGUI* guiObj, int xCenter, int yCenter){
    guiObj->drawBitmap(xCenter - 40, yCenter - 40, "PLAYDE.BMP");
}


void drawStartStopSelected(PanelGUI* guiObj, int xCenter, int yCenter){
    guiObj->drawBitmap(xCenter - 40, yCenter - 40, "PLAYSEL.BMP");
}

void drawNextDeSelected(PanelGUI* guiObj, int xCenter, int yCenter){
    guiObj->drawBitmap(xCenter - 40, yCenter - 40, "NEXTDE.BMP");
}


void drawNextSelected(PanelGUI* guiObj, int xCenter, int yCenter){
    guiObj->drawBitmap(xCenter - 40, yCenter - 40, "NEXTSEL.BMP");
}

void drawPrevDeSelected(PanelGUI* guiObj, int xCenter, int yCenter){
    guiObj->drawBitmap(xCenter - 40, yCenter - 40, "PREVDE.BMP");
}


void drawPrevSelected(PanelGUI* guiObj, int xCenter, int yCenter){
    guiObj->drawBitmap(xCenter - 40, yCenter - 40, "PREVSEL.BMP");
}

