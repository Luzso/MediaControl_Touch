#include "PanelGUI.h"

#define XPOINT first
#define YPOINT second

namespace startupanimation{

    struct DrawPattern{

        std::pair<int, int>* xypoints = nullptr;
        int nPoints = 0;
        const uint16_t color = ILI9488_WHITE;
    };

    void animateStartup(PanelGUI* gui);
    void animate(PanelGUI* gui, DrawPattern patterns[], int nPatterns, int duration_ms);
    void animateSides(PanelGUI* gui, int duration);
    DrawPattern drawBottomLineLeft();
    //void reverse(std::pair<int, int> points[]);
    int getMaxPoints(DrawPattern* patterns, int nPatterns);

}