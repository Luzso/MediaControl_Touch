#include "touch_gui.h"

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


TouchGui::TouchGui(){
    
    this->initializeTouchPanel();
   
}   

void TouchGui::initializeTouchPanel(){
    this->monitor = new ILI9488_t3(CS_PIN, DC_PIN, RST_PIN, MOSI_PIN, SCLK_PIN, MISO_PIN);
    this->monitor->begin();
    this->monitor->useFrameBuffer(true);
    this->monitor->setFrameBuffer(this->frame_buffer);
    this->monitor->setRotation(ROTATION);
    this->setSaveFont(Arial_12_Bold);
    // Test
    this->monitor->setTextColor(ILI9488_CYAN);
}

void TouchGui::clearScreen(){

    this->monitor->fillScreen(this->backgroundColor);
    this->monitor->updateScreen();
}

void TouchGui::setDefaultBackground(uint16_t color){

    this->backgroundColor = color;

}


void TouchGui::setSaveFont(const ILI9341_t3_font_t& font){
    this->monitor->setFont(font);
    this->currentFont = font;
}

ILI9341_t3_font_t TouchGui::getFont(){
    return this->currentFont;
}

FontSize TouchGui::getFontSize(){
    // Parse the font 
    FontSize size;
    size.width = this->currentFont.bits_width;
    size.height = currentFont.cap_height;

    return size;
}

void TouchGui::writeInBox(String text, int xBound1, int xBound2, int yBound1, int yBound2, bool doCenter){

    this->clearScreen();
    FontSize size = this->getFontSize();
    int numChars = text.length();

    int xStart = 0;
    int yStart = 0;
    if(doCenter){
        int dX = xBound2 - xBound1;
        int dY = yBound2 - yBound1;
        xStart = dX/2 - size.height/FONT_HEIGHT_WIDTH_RATIO*numChars / 2.0;
        yStart = dY/2 - size.height / 2.0;
    }
    xStart += xBound1;
    yStart += yBound1;

    monitor->setCursor(xStart, yStart);

    this->monitor->print(text);
    this->monitor->updateScreen();

}

