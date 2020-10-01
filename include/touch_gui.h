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

protected:
    
    PushButton playPauseBtn;
    PushButton *buttons[1] = {&playPauseBtn};
};