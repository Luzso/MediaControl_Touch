#include "push_button.h"
#include <vector>
#include <string>
#include "Wire.h"
#include "ILI9488_t3.h"
#include <URTouch.h>
#include <cstdint>

class TouchGui {

public:

    ILI9488_t3* monitor = NULL;
    URTouch* touch = NULL;
     
    TouchGui();

    void initializeTouchPanel();
    void getTouch();
    void setBackgroundColor(uint16_t color);
    void writeClearCenter(std::string text);
    void clearScreen();

protected:
    
    PushButton playPauseBtn;
    PushButton *buttons[1] = {&playPauseBtn};

private:

    uint16_t backgroundColor = ILI9488_BLACK;

};