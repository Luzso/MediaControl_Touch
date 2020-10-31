#include "push_button.h"
#include <vector>
#include <string>
#include "Wire.h"
#include "ILI9488_t3.h"
#include <URTouch.h>
#include <cstdint>
#include "String.h"
#include "ili9488_t3_font_ArialBold.h"
#include "EEPROM.h"

#define PIXELS_X 480
#define PIXELS_Y 320

struct FontSize{
    int width;
    int height;
};

enum Error{
    textError = 0,
    buttonsquareError
};

class PanelGUI {

public:

    ILI9488_t3* monitor = NULL;
    URTouch* touch = NULL;

    RAFB frame_buffer[ILI9488_TFTWIDTH * ILI9488_TFTHEIGHT];
     
    PanelGUI();

    void initGraphics();
    void setDefaultBackground(uint16_t color);
    void clearScreen();
    void drawButtonSquare(int x, int y, int width, int height, bool selected, bool update = true);
    void writeInBox_sizes(String text, int xStart, int yStart, int width, int height, bool doCenter, bool update = true);
    void writeInBox_boundaries(String text, int xBound1, int xBond2, int yBound1, int yBound2, bool doCenter, bool update = true);
    void clearRect(int x, int y, int width, int height, bool update = false);
    FontSize getFontSize();
    void setSaveFont(const ILI9341_t3_font_t& font);
    ILI9341_t3_font_t getFont();

    void drawError(Error error);

protected:
    
    PushButton playPauseBtn;
    PushButton *buttons[1] = {&playPauseBtn};

private:

    uint16_t backgroundColor = ILI9488_BLACK;
    ILI9341_t3_font_t currentFont = Arial_12_Bold;


};