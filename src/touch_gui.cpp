#include "touch_gui.h"
#include "ili9488_t3_font_ArialBold.h"

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

using namespace std;

TouchGui::TouchGui(){
    
    this->initializeTouchPanel();
   
}   


void TouchGui::initializeTouchPanel(){
    this->monitor = new ILI9488_t3(CS_PIN, DC_PIN, RST_PIN, MOSI_PIN, SCLK_PIN, MISO_PIN);
    this->monitor->begin();
    this->monitor->useFrameBuffer(true);
    this->monitor->setRotation(ROTATION);
    
    // Test
    this->monitor->setTextColor(ILI9488_CYAN);

}

void TouchGui::clearScreen(){

    this->monitor->fillScreen(this->backgroundColor);
    this->monitor->updateScreen();
}

void TouchGui::setBackgroundColor(uint16_t color){

    this->backgroundColor = color;

}

void TouchGui::writeClearCenter(string text){

    this->clearScreen();

    uint8_t textSizeX = 4;
    uint8_t textSizeY = 2;
    this->monitor->setTextSize(textSizeX, textSizeY);
    this->monitor->setCursor(PIXELS_X/2 - textSizeX/2*this->monitor->getTextSize(), PIXELS_Y/2);

    this->monitor->print(text.c_str());

    this->monitor->updateScreen();
}

void TouchGui::getTouch()
{
}

