#include "BasePanel.h"



class CalibrationPanel : public BasePanel
 {
    public:

    int lastX = 0;
    int lastY = 0;

    uint32_t cx, cy;
    uint32_t rx[8], ry[8];
    uint32_t clx, crx, cty, cby;
    float px, py;
    int dispx, dispy, text_y_center;
    uint32_t calx, caly, cals;
    char buf[13];


    CalibrationPanel();

    void startCalibration();
    void update();

    private:

    TextboxBackground textBackground;

    void writeReadXY(TouchCoords* xy);
    void initBackgroundVisuals();


};