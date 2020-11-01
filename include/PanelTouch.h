#include "EEPROMManager.h"
#include "URTouch.h"

struct XYCoords{

    XYCoords(uint16_t newX = 0, uint16_t newY = 0){
        this->x = newX;
        this->y = newY;
    }


    bool compare(XYCoords* other){
        return (this->x == other->x && this->y == other->y);
    }

    uint16_t x;
    uint16_t y;
};

class PanelTouch : public URTouch
{
public:
    PanelTouch();

    XYCoords getTouch();

    XYCoords prevTouch;
    bool hasTouch = false;
};