#include "MediaTouchPanel.h"
#include "MediaTouchGui.h"

MediaTouchPanel::MediaTouchPanel(PanelTouch* touch, PanelGUI* gui) 
    : BasePanel(touch, gui)
{
    this->drawMainUI();
    this->createButtons();
}

void MediaTouchPanel::drawMainUI(){
    int margin = 10;
    this->guiObj->monitor->drawRect(margin, margin, SCREEN_WIDTH - margin, SCREEN_HEIGHT - margin, ILI9488_WHITE);

}



void MediaTouchPanel::createButtons(){
    this->nButtons = 3;
    this->buttons = new Button[nButtons] {
        Button(guiObj, &onBtn_startPause, &drawStartStopDS, &drawStartStopS, SCREEN_WIDTH/2, SCREEN_HEIGHT/2, 75, 75),
        Button(guiObj, &onBtn_next, &drawStartStopDS, &drawStartStopS, SCREEN_WIDTH / 2 + 100, SCREEN_HEIGHT / 2, 75, 75),
        Button(guiObj, &onBtn_previous, &drawStartStopDS, &drawStartStopS, SCREEN_WIDTH / 2 - 100, SCREEN_HEIGHT / 2, 75, 75)}; // Add position and dimensions

}


void MediaTouchPanel::onBtn_startPause(){
    Keyboard.press(KEY_MEDIA_PLAY_PAUSE);
    Keyboard.release(KEY_MEDIA_PLAY_PAUSE);
}

void MediaTouchPanel::onBtn_next(){
    Keyboard.press(KEY_MEDIA_NEXT_TRACK);
    Keyboard.release(KEY_MEDIA_NEXT_TRACK);
}

void MediaTouchPanel::onBtn_previous(){
    Keyboard.press(KEY_MEDIA_PREV_TRACK);
    Keyboard.release(KEY_MEDIA_PREV_TRACK);
}