#pragma once

#include "BasePanel.h"

#define N_CALIB_POINTS 8

enum orientation{
    landscape,
    portrait
};

class CalibrationPanel : public BasePanel
 {
    public:
    CalibrationPanel(PanelTouch* touch, PanelGUI* gui, orientation orientation);

    int lastX = 0;
    int lastY = 0;

    uint32_t cx, cy;
    uint32_t rx[8], ry[8];
    uint32_t clx, crx, cty, cby;
    float px, py;
    int dispx = SCREEN_WIDTH, dispy = SCREEN_HEIGHT;
    int text_y_center;
    char buf[13];
    uint32_t calx, caly, cals;
    

    void startCalibration();
    void update();

    private:

    orientation ori;
    TextboxBackground textBackground;
    
    XYCoords crossHairPositions[N_CALIB_POINTS]= {
        XYCoords(10, 10),
        XYCoords(10, SCREEN_HEIGHT/ 2),
        XYCoords(10, SCREEN_HEIGHT - 11),
        XYCoords(SCREEN_WIDTH / 2, 10),
        XYCoords(SCREEN_WIDTH / 2, SCREEN_HEIGHT - 11),
        XYCoords(SCREEN_WIDTH - 11, 10),
        XYCoords(SCREEN_WIDTH - 10, SCREEN_HEIGHT / 2),
        XYCoords(SCREEN_WIDTH - 11, SCREEN_HEIGHT - 11)
        };



    void writeReadXY(XYCoords* xy);
    void initBackgroundVisuals();
    void clearCalibSpace();
    void calibrate(int x, int y, int i);
    void readCoordinates();
    void getCalibTouchPoints();
    void calculateCalibration();
    void finishCalibration();
    void toHex(uint32_t num);
    void waitForTouch();
    void fail();

};