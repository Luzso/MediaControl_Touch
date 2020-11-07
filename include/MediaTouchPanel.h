#pragma once

#include "BasePanel.h"

class MediaTouchPanel : public BasePanel
{

public:
    MediaTouchPanel(PanelTouch* touch, PanelGUI* gui);
    
    static void onBtn_startPause();
    static void onBtn_next();
    static void onBtn_previous();

private: 

    void drawMainUI();
    void createButtons();
};