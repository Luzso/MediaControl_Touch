#include <Arduino.h>
#include "touch_gui.h"


TouchGui* mediaPlayer;

int i = 0;

void setup(){
    mediaPlayer = new TouchGui();
    delay(100);
    mediaPlayer->writeClearCenter("Hello Annaaa!");
}

void loop(){
    //i++;
    //mediaPlayer->writeClearCenter("Hello" + 1);
    //delay(1000);
}

