#include "PanelTouch.h"
#include "PanelGUI.h"
#include "Button.h"

class BasePanel : public PanelTouch, public PanelGUI
{

    public:
    BasePanel(URTouch* touchObj);

    
    int nButtons = 0;
    int nLoadedButtons = 0;
    Button* buttons;

    protected:

    virtual void createButtons();
    void addButton(String name, void(*btnFunc)(), int x, int y, int width, int height);
    
};