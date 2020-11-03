#include "PanelTouch.h"
#include "PanelGUI.h"


class BasePanel : public PanelTouch, public PanelGUI
{

public:
    BasePanel(URTouch* touchObj);
    
    void performTouchCalibration();
};