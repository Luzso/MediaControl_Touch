#include "MediaTouchPanel.h"
#include "MediaTouchGui.h"

MediaTouchPanel::MediaTouchPanel(PanelTouch* touch, PanelGUI* gui) 
    : BasePanel(touch, gui)
{
    this->drawMainUI();
    this->createButtons();
}

void MediaTouchPanel::drawMainUI(){
    /*
    int margin = 10;
    this->guiObj->monitor->drawRect(margin, margin, SCREEN_WIDTH - margin, SCREEN_HEIGHT - margin, ILI9488_WHITE);*/

    this->guiObj->drawBitmap(0, 0, "DEFAUL~1.BMP");

}



void MediaTouchPanel::createButtons(){
    this->nButtons = 3;
    this->buttons = new Button[nButtons] {
        Button(guiObj, &onBtn_startPause, &drawStartStopDeSelected, &drawStartStopSelected, SCREEN_WIDTH/2, SCREEN_HEIGHT/2, 75, 75),
        Button(guiObj, &onBtn_next, &drawNextDeSelected, &drawNextSelected, SCREEN_WIDTH / 2 + 125, SCREEN_HEIGHT / 2, 75, 75),
        Button(guiObj, &onBtn_previous, &drawPrevDeSelected, &drawPrevSelected, SCREEN_WIDTH / 2 - 125, SCREEN_HEIGHT / 2, 75, 75)}; // Add position and dimensions

}


void MediaTouchPanel::onBtn_startPause(){
    Serial.println("Media key pressed: Start/Pause");
    Keyboard.press(KEY_MEDIA_PLAY_PAUSE);
    Keyboard.release(KEY_MEDIA_PLAY_PAUSE);
}

void MediaTouchPanel::onBtn_next(){
    Serial.println("Media key pressed: Next");
    Keyboard.press(KEY_MEDIA_NEXT_TRACK);
    Keyboard.release(KEY_MEDIA_NEXT_TRACK);
}

void MediaTouchPanel::onBtn_previous(){
    Serial.println("Media key pressed: Previous");
    Keyboard.press(KEY_MEDIA_PREV_TRACK);
    Keyboard.release(KEY_MEDIA_PREV_TRACK);
}