#include "PanelTouch.h"

#define PIN_CLK 0
#define PIN_CS 0
#define PIN_DIN 0
#define PIN_DO 0
#define PIN_IRQ 0

PanelTouch::PanelTouch() : URTouch(PIN_CLK, PIN_CS, PIN_DIN, PIN_DO, PIN_IRQ) {

    InitTouch(LANDSCAPE);

}