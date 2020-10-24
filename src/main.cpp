#include <Arduino.h>
#include "touch_gui.h"


TouchGui* mediaPlayer;

int i = 0;

void setup(){

    mediaPlayer = new TouchGui();
    delay(100);

    String displayString = String("Hello Annaaa!!!") + mediaPlayer->getFontSize().height;
    mediaPlayer->writeInBox(displayString, 0, PIXELS_X, 0, PIXELS_Y, true);
}

void loop(){
  
    
}

