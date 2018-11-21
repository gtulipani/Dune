#ifndef __PANEL_BUTTON_H__
#define __PANEL_BUTTON_H__

// Commons Libraries
#include <Point.h>

// Client Libraries
#include "../sdl/SdlTexture.h"

class PanelButton {
private:
    int width;
    int height;
    Point screen_position;
    std::string action;
    SdlTexture *texture;

public:
    PanelButton(int width, int height, Point screen_position, std::string action, SdlTexture *texture);

    PanelButton(int width, int height, Point screen_position, std::string action, std::string image_path, SdlWindow* window);

    void render(int offset_x, int offset_y);

    bool includesPosition(Point point) const;

    bool includesExternalAction() const;

    std::string getAction() const;
};


#endif //__PANEL_BUTTON_H__
