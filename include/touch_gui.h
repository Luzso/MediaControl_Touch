#include "push_button.h"
#include <vector>
#include <string>
#include "Wire.h"
#include "ILI9488_t3.h"
#include <URTouch.h>
#include <cstdint>
#include "String.h"
#include "ili9488_t3_font_ArialBold.h"

struct FontSize{
    int width;
    int height;
};

class TouchGui {

public:

    ILI9488_t3* monitor = NULL;
    URTouch* touch = NULL;

    RAFB frame_buffer[ILI9488_TFTWIDTH * ILI9488_TFTHEIGHT];
     
    TouchGui();

    void initializeTouchPanel();
    void setDefaultBackground(uint16_t color);
    void writeClearCenter(String text);
    void clearScreen();
    FontSize getFontSize();
    void setSaveFont(const ILI9341_t3_font_t& font);
    ILI9341_t3_font_t getFont();

protected:
    
    PushButton playPauseBtn;
    PushButton *buttons[1] = {&playPauseBtn};

private:

    uint16_t backgroundColor = ILI9488_BLACK;
    ILI9341_t3_font_t currentFont = Arial_12_Bold;

};