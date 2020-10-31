#include <Arduino.h>
#include "PanelGUI.h"


PanelGUI* mediaPlayer;

int i = 0;

void setup(){

    mediaPlayer = new PanelGUI();
    delay(100);

    String displayString = String("Hello Annaaa!!!") + mediaPlayer->getFontSize().height;
    
    mediaPlayer->clearScreen();
    mediaPlayer->drawButtonSquare(50, 30, 75, 75, true);  
    mediaPlayer->writeInBox_sizes(displayString, 50, 30, 100, 100, true);
    
}

void loop(){
  
    
}

