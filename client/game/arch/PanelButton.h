#ifndef __PANEL_BUTTON_H__
#define __PANEL_BUTTON_H__

// Client Libraries
#include "../sdl/SdlTexture.h"

class PanelButton {
private:
    int id;
    int width;
    int height;
    SdlTexture texture;

public:
    PanelButton(int id, int width, int height, SdlTexture texture);

    PanelButton(int id, int width, int height, std::string image_path, SdlWindow* window);

    void render(int offset_x, int offset_y);
};


#endif //__PANEL_BUTTON_H__
