#include "push_button.h"
#include <vector>
#include <string>
#include "Wire.h"

class TouchGui {

public:

    uint16_t ID = 1337;
    void setup();
    void getTouch();
    void blackScreen();

protected:
    
    PushButton playPauseBtn;
    PushButton *buttons[1] = {&playPauseBtn};
};