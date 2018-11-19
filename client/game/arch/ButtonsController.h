#ifndef __BUTTONS_CONTROLLER_H__
#define __BUTTONS_CONTROLLER_H__

// STL Libraries
#include <vector>

// Client Libraries
#include "../sdl/SdlWindow.h"
#include "../sdl/SdlTexture.h"
#include "PanelButton.h"

class ButtonsController {
private:
    SdlWindow *window;

    SdlTexture panel_texture{};

    std::vector<PanelButton> buttons{};

    int screen_width{};
    int screen_height{};

    int screen_width_offset{};

    void buildButtons();
public:
    explicit ButtonsController(SdlWindow *window);

    void fill();

    void configure(int screen_width, int screen_height, int screen_width_offset);

    void render();

    void loadButtonsPanel();
};


#endif //__BUTTONS_CONTROLLER_H__
