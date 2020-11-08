#include "StartupAnimation.h"
#include "PanelGUI.h"

using namespace startupanimation;


void startupanimation::animateStartup(PanelGUI* gui){

    animateSides(gui, 500);

}

void startupanimation::animateSides(PanelGUI* gui, int duration_ms){
    int nPatterns = 1;
    DrawPattern patterns[nPatterns]{drawBottomLineLeft()};
    animate(gui, patterns, nPatterns, duration_ms);
}

void startupanimation::animate(PanelGUI* gui, DrawPattern patterns[], int nPatterns, int duration_ms){
    int maxPoints = 190; //getMaxPoints(patterns);

    int step_ms = duration_ms / maxPoints;
    for(int i_point = 0; i_point < maxPoints; i_point++){
        for(int i_pattern = 0; i_pattern < nPatterns ; i_pattern++){
            gui->monitor->drawPixel(patterns[i_pattern].xypoints[i_point].XPOINT, 
                                    patterns[i_pattern].xypoints[i_point].YPOINT,
                                    patterns[i_pattern].color);
        }
        delay(step_ms);
    }

    gui->monitor->setCursor(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);
    gui->monitor->print(sizeof(patterns));
}

DrawPattern startupanimation::drawBottomLineLeft(){
    
    DrawPattern retDraw;

    int xStart = SCREEN_WIDTH/2; 
    int xEnd = 50;

    retDraw.nPoints = xStart - xEnd;
    int y = SCREEN_HEIGHT - 10;
    retDraw.xypoints = new std::pair<int, int>[retDraw.nPoints];
    for(int i_point = 0; i_point < retDraw.nPoints; i_point++){
        retDraw.xypoints[i_point].XPOINT = SCREEN_WIDTH / 2 - i_point;
        retDraw.xypoints[i_point].YPOINT = y;
    }

    return retDraw;

}

/*
void startupanimation::reverse(std::pair<int, int> points[]){
    int nPoints = sizeof(points) / sizeof(std::pair<int, int>);
    reverse(points, points + nPoints);
}
*/

int startupanimation::getMaxPoints(DrawPattern* patterns, int nPatterns){
    int max_v = 0;
 
	for ( int i = 0; i < nPatterns; i++ )
	{
		if ( patterns[i].nPoints > max_v )
		{
			max_v = patterns[i].nPoints;
		}
	}

    
    return max_v;
}