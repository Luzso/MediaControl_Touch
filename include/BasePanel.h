#pragma once

#include "Button.h"
#include "PanelGUI.h"
#include "PanelTouch.h"

class BasePanel
{

    public:
    BasePanel(PanelTouch* touch, PanelGUI* gui);  
    
    int nButtons = 0;
    int nLoadedButtons = 0;
    Button* buttons;

    PanelGUI* guiObj = nullptr;
    PanelTouch* touchObj = nullptr;

    void update();
};