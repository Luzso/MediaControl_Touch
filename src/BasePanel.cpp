#include "BasePanel.h"

BasePanel::BasePanel(URTouch* touchObj) 
    : PanelTouch(touchObj), PanelGUI()
{
    // Recall calibration from FLASH
}



void BasePanel::addButton(String name, void(*btnFunc)(), int x, int y, int width, int height) {
    this->nLoadedButtons++;
    if(this->nLoadedButtons <= this->nButtons){
        this->buttons[nLoadedButtons-1] = Button(btnFunc); // Add position and dimenstions
    }
    
}

void BasePanel::createButtons() {

}