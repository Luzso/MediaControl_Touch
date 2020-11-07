#pragma once

#include "PanelGUI.h"

class Button {
    public:

    Button(
        PanelGUI* gui = nullptr,
        void(*btnCallback)() = nullptr, 
        void(*drawDeselected)(PanelGUI*, int, int) = nullptr, 
        void(*drawSelected)(PanelGUI*, int, int) = nullptr, 
        int x = 0, 
        int y = 0, 
        int width = 0, 
        int height = 0);

    bool wasPressed(int xTouched, int yTouched);
    void press();
    void deSelect();

    private:

    PanelGUI* guiObj = nullptr;
    
    bool active = true;
    int xCenter = 0;
    int yCenter = 0;
    int touchWidth = 0;
    int touchHeight = 0;
    bool selected = false;

    void (*btnPressCallback)() = nullptr;
    void (*drawDS)(PanelGUI*, int, int) = nullptr;
    void (*drawS)(PanelGUI*, int, int) = nullptr;
    void setBtnCallback(void (*btnCallBack)());
    void setPosition(int x, int y);
    void setDimensions(int width, int height);

    
    
};