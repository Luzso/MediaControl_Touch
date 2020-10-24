#include "touch_gui.h"
#include "ili9488_t3_font_ArialBold.h"

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

TouchGui::TouchGui(){
    
    this->initializeTouchPanel();
   
}   


void TouchGui::initializeTouchPanel(){
    this->monitor = new ILI9488_t3(CS_PIN, DC_PIN, RST_PIN, MOSI_PIN, SCLK_PIN, MISO_PIN);
    this->monitor->begin();
    this->monitor->useFrameBuffer(true);
    this->monitor->setRotation(ROTATION);
    
    // Test
    this->monitor->fillScreen(ILI9488_BLUE);
    this->monitor->drawCircle(150, 150, 50, ILI9488_DARKCYAN);
    this->monitor->setCursor(10, 10);
    this->monitor->setFont(Arial_12_Bold);
    this->monitor->setTextColor(ILI9488_CYAN);
    this->monitor->println();
    this->monitor->println("- Hello there.");
    this->monitor->println("- General Kenobi.");
    this->monitor->updateScreen();

}

void TouchGui::getTouch()
{
}

