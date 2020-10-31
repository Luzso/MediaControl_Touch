#include "PanelGUI.h"

#define CS_PIN 21
#define DC_PIN 20
#define RST_PIN 255 // 3.3V
#define SCLK_PIN 14
#define MOSI_PIN 7
#define MISO_PIN 12

#define TCKL_PIN 0
#define TCS_PIN 0
#define TDIN_PIN 0
#define DOUT_PIN 0
#define IRQ_PIN 0

#define ROTATION 3 // Horizontal

#define FONT_HEIGHT_WIDTH_RATIO 1.3333f



PanelGUI::PanelGUI(){
    
    this->initGraphics();
   
}   

void PanelGUI::initGraphics(){
    this->monitor = new ILI9488_t3(CS_PIN, DC_PIN, RST_PIN, MOSI_PIN, SCLK_PIN, MISO_PIN);
    this->monitor->begin();
    this->monitor->useFrameBuffer(true);
    this->monitor->setFrameBuffer(this->frame_buffer);
    this->monitor->setRotation(ROTATION);
    this->setSaveFont(Arial_12_Bold);
    // Test
    this->monitor->setTextColor(ILI9488_CYAN);
}

void PanelGUI::clearScreen(){

    this->monitor->fillScreen(this->backgroundColor);
    this->monitor->updateScreen();
}

void PanelGUI::setDefaultBackground(uint16_t color){

    this->backgroundColor = color;

}

// BUTTON GRAPHICS
void PanelGUI::drawButtonSquare(int x, int y, int width, int height, bool selected, bool update){
    if( x + width <= SCREEN_WIDTH && y + height <= SCREEN_HEIGHT){
        this->clearRect(x, y, width, height);

        uint16_t color = ILI9488_CYAN;
        this->monitor->drawRect(x, y, width, height, color);

        int margin = 3;
        uint16_t selectedColor = ILI9488_NAVY;
        this->monitor->fillRect(x + margin, y + margin, width - margin*2, height - margin*2, selectedColor);

        if(update)
            this->monitor->updateScreen();
    }
    else{
        this->drawError(buttonsquareError);
    }
}

void PanelGUI::drawCrossHair(int x, int y){
    int outerWidth = 20;
    int outerHeight = 20;

    int rectStartX = x - outerWidth / 2;
    int rectStartY = y - outerHeight / 2;
    this->clearRect(rectStartX, rectStartY, outerWidth, outerHeight);

    this->monitor->drawRect(rectStartX, rectStartY, outerWidth, outerHeight, ILI9488_WHITE);
    this->monitor->drawLine(x - outerWidth / 4, y, x + outerWidth /4, y, ILI9488_WHITE);
    this->monitor->drawLine(x, y - outerHeight / 4, x, y + outerHeight / 4, ILI9488_WHITE);

    this->monitor->updateScreen();
}

// TEXT EDITING

void PanelGUI::setSaveFont(const ILI9341_t3_font_t& font){
    this->monitor->setFont(font);
    this->currentFont = font;
}

ILI9341_t3_font_t PanelGUI::getFont(){
    return this->currentFont;
}

FontSize PanelGUI::getFontSize(){
    // Parse the font 
    FontSize size;
    size.width = this->currentFont.bits_width;
    size.height = currentFont.cap_height;

    return size;
}


void PanelGUI::writeInBox_boundaries(String text, int xStart, int xEnd, int yStart, int yEnd, bool doCenter, TextboxBackground background, bool update){
    int width = xEnd - xStart;
    int height = yEnd - yStart;

    this->writeInBox_sizes(text, xStart, yStart, width, height, doCenter, background, update);
}

void PanelGUI::writeInBox_sizes(String text, int x, int y, int width, int height, bool doCenter, TextboxBackground background, bool update){

    FontSize size = this->getFontSize();
    int numChars = text.length();

    int xOrigin = 0;
    int yOrigin = 0;
    int textWidth = size.height/FONT_HEIGHT_WIDTH_RATIO*numChars;
    int textHeight = size.height;
    if(x >= 0 && y >= 0 && x + width <= SCREEN_WIDTH && y + height <= SCREEN_HEIGHT){
        if(doCenter){
            xOrigin = width/2 - textWidth / 2.0;
            yOrigin = width/2 - textHeight / 2.0;
        }
        xOrigin += x;
        yOrigin += y;
    }
    else{
        this->drawError(textError);
    }
    if(background.useDefaultBackground)
        this->clearRect(xOrigin, yOrigin, textWidth, textHeight + 3); // +3 to account for commas
    else
        this->monitor->fillRect(xOrigin, yOrigin, textWidth, textHeight, background.color);

    monitor->setCursor(xOrigin, yOrigin);
    this->monitor->print(text);

    if(update)
        this->monitor->updateScreen();

}

void PanelGUI::clearRect(int x, int y, int width, int height, bool doUpdate){
    this->monitor->fillRect(x, y, width, height, this->backgroundColor);

    if(doUpdate)
        this->monitor->updateScreen();
}

void PanelGUI::drawError(Error error){
    int width = 5;
    int height = 5;
    int x = SCREEN_WIDTH - width;
    int y =SCREEN_HEIGHT - height;

    this->monitor->setCursor(x, y);
    this->monitor->fillRect(x, y, width, height, ILI9488_RED);
    this->monitor->updateScreen();
}

