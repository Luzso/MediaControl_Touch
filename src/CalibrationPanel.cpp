#include "CalibrationPanel.h"



CalibrationPanel::CalibrationPanel(orientation orientation) 
    : BasePanel()
{
    this->ori = orientation;

    textBackground.color = ILI9488_DARKGREY;
    textBackground.useDefaultBackground = false;
}


void CalibrationPanel::startCalibration(){
    this->initBackgroundVisuals();
    this->getCalibTouchPoints();
    this->calculateCalibration();
    //this->printCalibrationData();
    
}

void CalibrationPanel::getCalibTouchPoints() {
      
    for(int i_pos = 0; i_pos < N_CALIB_POINTS; i_pos++){
        calibrate(crossHairPositions[i_pos].x, crossHairPositions[i_pos].y, i_pos);
    }

}

void CalibrationPanel::calculateCalibration(){
    if(this->ori == landscape)
        cals = (long(dispx - 1) << 12) + (dispy -1);
    else
        cals = (long(dispy - 1) << 12) + (dispx -1);
    
    if(this->ori == portrait)
        px = abs(((float(rx[2] + rx[4] + rx[7]) / 3) - (float(rx[0]+rx[3]+rx[5])/3))/(dispy-20));
    else
        px = abs(((float(rx[5]+rx[6]+rx[7])/3)-(float(rx[0]+rx[1]+rx[2])/3))/(dispy-20));  // LANDSCAPE

    if(this->ori == portrait){
        clx = (((rx[0]+rx[3]+rx[5])/3));
        crx = (((rx[2]+rx[4]+rx[7])/3));
    }
    else
    {
        clx = (((rx[0] + rx[1] + rx[2]) / 3));
        crx = (((rx[5] + rx[6] + rx[7]) / 3));
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

void CalibrationPanel::calibrate(int x, int y, int i){
    this->drawCrossHair(x, y, ILI9488_WHITE);
    readCoordinates();
    this->drawCrossHair(x,y, ILI9488_GREEN);
    rx[i] = cx;
    ry[i] = cy;

    while(this->dataAvailable() == true) {}
}

void CalibrationPanel::readCoordinates(){
    int iter = 5000;
    int failcount = 0;
    int cnt = 0;
    uint32_t tx = 0;
    uint32_t ty = 0;
    boolean OK = false;

    while(OK == false){
        while((this->dataAvailable() == true) && (cnt < iter) && (failcount < 10000)){
            this->calibrateRead();
            if(!((this->TP_X == 65535) || (this->TP_Y==65535)))
            {
                tx += this->TP_X;
                ty += this->TP_Y;
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

void CalibrationPanel::fail(){
    
}

void CalibrationPanel::update(){
    
    XYCoords touch = this->getTouch();
    if(this->hasTouch){

        writeReadXY(&touch);
    }
    else{
        touch = XYCoords(0,0);
        writeReadXY(&touch);
    }

    delay(100); // Replace with timer check
}


void CalibrationPanel::initBackgroundVisuals(){
    this->clearScreen();
    this->setSaveFont(Arial_12);
    this->writeInBox_sizes("Calibrating.", 0, 0, SCREEN_WIDTH, 320, true, TextboxBackground(), false);
}


void CalibrationPanel::writeReadXY(XYCoords* xy){
    String xyString = String(xy->x) + ", " + String(xy->y);
    this->monitor->fillRect(100, SCREEN_HEIGHT - 30, 100, 30, textBackground.color);

    this->writeInBox_sizes(xyString, 100, SCREEN_HEIGHT - 20, 35, 10, false, this->textBackground, false);
}

void CalibrationPanel::clearCalibSpace(){
    int margin = 50;
    this->clearRect(margin, margin, SCREEN_WIDTH - margin, SCREEN_HEIGHT - margin * 2, true);
}