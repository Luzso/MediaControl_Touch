#include "CalibrationPanel.h"



CalibrationPanel::CalibrationPanel(PanelTouch* touch, PanelGUI* gui,  orientation orientation) 
    : BasePanel(touch, gui)
{
    this->ori = orientation;

    textBackground.color = ILI9488_DARKGREY;
    textBackground.useDefaultBackground = false;
}


void CalibrationPanel::startCalibration(){
    this->initBackgroundVisuals();
    this->getCalibTouchPoints();
    this->calculateCalibration();
    this->finishCalibration();
    //this->printCalibrationData();
    
}

void CalibrationPanel::getCalibTouchPoints() {
      
    for(int i_pos = 0; i_pos < N_CALIB_POINTS; i_pos++){
        calibrate(crossHairPositions[i_pos].x, crossHairPositions[i_pos].y, i_pos);
    }

}

void CalibrationPanel::readCoordinates(){
    int iter = 5000;
    int failcount = 0;
    int cnt = 0;
    uint32_t tx = 0;
    uint32_t ty = 0;
    boolean OK = false;

    while(OK == false){
        this->guiObj->clearRect(SCREEN_WIDTH / 2 - 50, 50, 200, 30);
        this->guiObj->writeInBox_sizes("PRESS", SCREEN_WIDTH / 2 - 50, 50, 200, 30, false, TextboxBackground());
        while (this->touchObj->dataAvailable() == false) {}
        this->guiObj->clearRect(SCREEN_WIDTH / 2 - 50, 50, 200, 30);
        this->guiObj->writeInBox_sizes("HOLD", SCREEN_WIDTH / 2 - 50, 50, 200, 30, false, TextboxBackground());
        while((this->touchObj->dataAvailable() == true) && (cnt < iter) && (failcount < 10000)){
            this->touchObj->calibrateRead();
            if(!((this->touchObj->TP_X == 65535) || (this->touchObj->TP_Y==65535)))
            {
                tx += this->touchObj->TP_X;
                ty += this->touchObj->TP_Y;
                cnt++;
            }
            else
                failcount++;
        }
        if(cnt >= iter){
            OK = true;
        }
        else{
            tx = 0;
            ty = 0;
            cnt = 0;
        }
        if(failcount >= 10000)
            fail();
    }

    cx = tx / iter;
    cy = ty / iter;
}


void CalibrationPanel::calibrate(int x, int y, int i){
    this->guiObj->drawCrossHair(x, y, ILI9488_WHITE);
    readCoordinates();
    this->guiObj->clearRect(SCREEN_WIDTH / 2 - 50, 50, 200, 30);
    this->guiObj->writeInBox_sizes("RELEASE", SCREEN_WIDTH / 2 - 50, 50, 200, 30, false, TextboxBackground());
    this->guiObj->drawCrossHair(x, y, ILI9488_GREEN);
    rx[i] = cx;
    ry[i] = cy;

    while(this->touchObj->dataAvailable() == true) {}
}


void CalibrationPanel::calculateCalibration(){
    if(this->ori == landscape)
        cals = (long(dispx - 1) << 12) + (dispy -1);
    else
        cals = (long(dispy - 1) << 12) + (dispx -1);
    
    if(this->ori == portrait)
        px = abs(((float(rx[2] + rx[4] + rx[7]) / 3) - (float(rx[0] + rx[3] + rx[5]) / 3))/(dispy-20));
    else
        px = abs(((float(rx[5] + rx[6] + rx[7]) / 3) - (float(rx[0] + rx[1] + rx[2]) / 3))/(dispy-20));  // LANDSCAPE

    if(this->ori == portrait){
        clx = (((rx[0]+rx[3]+rx[5])/3));
        crx = (((rx[2]+rx[4]+rx[7])/3));
    }
    else
    {
        clx = (((rx[0] + rx[1] + rx[2]) / 3));
        crx = (((rx[5] + rx[6] + rx[7]) / 3));
    }
     
    if (clx<crx)
    {
        clx = clx - (px*10);
        crx = crx + (px*10);
    }
    else
    {
        clx = clx + (px*10);
        crx = crx - (px*10);
    }


    if (this->ori == portrait)
        py = abs(((float(ry[5]+ry[6]+ry[7])/3)-(float(ry[0]+ry[1]+ry[2])/3))/(dispx-20));  // PORTRAIT
    else
        py = abs(((float(ry[0]+ry[3]+ry[5])/3)-(float(ry[2]+ry[4]+ry[7])/3))/(dispx-20));  // LANDSCAPE

    if (this->ori == portrait)
    {
        cty = (((ry[5]+ry[6]+ry[7])/3));  // PORTRAIT
        cby = (((ry[0]+ry[1]+ry[2])/3));  // PORTRAIT
    }
    else
    {
        cty = (((ry[0]+ry[3]+ry[5])/3));  // LANDSCAPE
        cby = (((ry[2]+ry[4]+ry[7])/3));  // LANDSCAPE
    }
    if (cty<cby)
    {
        cty = cty - (py*10);
        cby = cby + (py*10);
    }
    else
    {
        cty = cty + (py*10);
        cby = cby - (py*10);
    }
    
    calx = (long(clx)<<14) + long(crx);
    caly = (long(cty)<<14) + long(cby);
    if (this->ori == landscape)
        cals = cals + (1L<<31);

        
}



void CalibrationPanel::waitForTouch()
{
  while (this->touchObj->dataAvailable() == true) {}
  while (this->touchObj->dataAvailable() == false) {}
  while (this->touchObj->dataAvailable() == true) {}
}

void CalibrationPanel::finishCalibration(){

    this->guiObj->monitor->setCursor(SCREEN_WIDTH / 2 - 45, SCREEN_HEIGHT / 2 + 20);
    toHex(calx);
    this->guiObj->monitor->print(buf);
    this->guiObj->monitor->setCursor(SCREEN_WIDTH / 2 - 45, SCREEN_HEIGHT / 2 + 40);
    toHex(caly);
    this->guiObj->monitor->print(buf);
    this->guiObj->monitor->setCursor(SCREEN_WIDTH / 2 - 45, SCREEN_HEIGHT / 2 + 60);
    toHex(cals);
    this->guiObj->monitor->print(buf);
    
}

void CalibrationPanel::fail(){
    
}

void CalibrationPanel::update(){
    static int inc = 0;
    XYCoords touchPoint = this->touchObj->getTouchDown();
    if(this->touchObj->hasTouch){
        writeReadXY(&touchPoint);
        this->guiObj->monitor->drawPixel(touchPoint.x, touchPoint.y, ILI9488_WHITE);
    }
}

void CalibrationPanel::initBackgroundVisuals(){

    text_y_center=(dispy/2)-6;
    this->guiObj->clearScreen();
    this->guiObj->setSaveFont(Arial_12);
    this->guiObj->writeInBox_sizes("Calibrating.", 0, 0, SCREEN_WIDTH, 320, true, TextboxBackground(), false);

}


void CalibrationPanel::writeReadXY(XYCoords* xy){
    String xyString = String(xy->x) + ", " + String(xy->y);
    this->guiObj->clearRect(SCREEN_WIDTH / 2 - 100, SCREEN_HEIGHT / 2 - 50, 200, 30);
    this->guiObj->writeInBox_sizes(xyString, SCREEN_WIDTH / 2 - 100, SCREEN_HEIGHT / 2 - 50, 200, 30, true, TextboxBackground(), false);
}


void CalibrationPanel::toHex(uint32_t num){
    buf[0] = '0';
    buf[1] = 'x';
    buf[10] = 'U';
    buf[11] = 'L';
    buf[12] = 0;
    for (int zz=9; zz>1; zz--)
    {
        if ((num & 0xF) > 9)
            buf[zz] = (num & 0xF) + 55;
        else
            buf[zz] = (num & 0xF) + 48;
        num=num>>4;
    }
}

void CalibrationPanel::clearCalibSpace(){
    int margin = 50;
    this->guiObj->clearRect(margin, margin, SCREEN_WIDTH - margin, SCREEN_HEIGHT - margin * 2, true);
}
