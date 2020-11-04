#include "BasePanel.h"

class MediaTouchPanel : BasePanel
{

public:
    MediaTouchPanel(URTouch* touchObj);
    
    void update();
    static void onBtn_startPause();

private: 

    void drawMainUI();
    void createButtons();
};