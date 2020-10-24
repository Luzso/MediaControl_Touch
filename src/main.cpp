#include <Arduino.h>
#include "touch_gui.h"


TouchGui* mediaPlayer;

int i = 0;

void setup(){

    mediaPlayer = new TouchGui();
    delay(100);

    String displayString = String("Hello Annaaa!") + String(mediaPlayer->monitor->getTextSize());
    mediaPlayer->writeClearCenter(String("Hi there"));
}

void loop(){
    //delay(1000);
    //mediaPlayer->writeClearCenter(String("Hi"));

    
}

