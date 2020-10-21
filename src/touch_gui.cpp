#include "touch_gui.h"

#define CS_PIN 21
#define DC_PIN 20
#define RST_PIN 255   
#define SCLK_PIN 14
#define MOSI_PIN 7
#define MISO_PIN 12

#define TCKL_PIN 0
#define TCS_PIN 0
#define TDIN_PIN 0
#define DOUT_PIN 0
#define IRQ_PIN 0

#define ROTATION 3 // Horizontal

#define PIXELS_X 480
#define PIXELS_Y 320


TouchGui::TouchGui(){
    
    this->initializeTouchPanel();
   
}   

void TouchGui::initializeTouchPanel(){
    this->monitor = new ILI9488_t3(CS_PIN, DC_PIN, RST_PIN, MOSI_PIN, SCLK_PIN, MISO_PIN);
    this->monitor->begin();
    this->monitor->useFrameBuffer(true);
    this->monitor->setFrameBuffer(this->frame_buffer);
    this->monitor->setRotation(ROTATION);
    this->setSaveFont(Arial_24_Bold);
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

void TouchGui::writeClearCenter(String text){

    this->clearScreen();
    FontSize size = this->getFontSize();
    int numChars = text.length();
    this->monitor->setCursor(PIXELS_X/2 - size.width*numChars / 2.0 , PIXELS_Y/2 - size.height / 2.0);
    this->monitor->print(text);
    this->monitor->updateScreen();

}

