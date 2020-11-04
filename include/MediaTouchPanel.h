#include "BasePanel.h"

class MediaTouchPanel : BasePanel
{

public:
    MediaTouchPanel(URTouch* touchObj);
    
    void update();
private: 
    void drawMainUI();
};