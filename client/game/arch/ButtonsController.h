#ifndef __BUTTONS_CONTROLLER_H__
#define __BUTTONS_CONTROLLER_H__

// STL Libraries
#include <vector>

// Client Libraries
#include "../sdl/SdlWindow.h"
#include "../sdl/SdlTexture.h"
#include "PanelButton.h"

class SDL_MouseButtonEvent;
class EventsLooperThread;

class ButtonsController {
private:
    SdlWindow *window;

    SdlTexture panel_texture{};

    std::vector<PanelButton> mandatory_buttons{};
    std::vector<PanelButton> optional_buttons{};

    int screen_width{};
    int screen_height{};

    int screen_width_offset{};

    void buildButtons();

    Point getGlobalPosition(Point point);
    Point getRelativePosition(Point point);

    // This method is used to calculate the position for each one of the main buttons, which are one next to each other
    Point buildMainButtonRelativePosition(int order);

    // This method is used to calculate the position for each one of the building icons, which are one above each other
    Point buildOptionalButtonRelativePosition(int order);
public:
    explicit ButtonsController(SdlWindow *window);

    void fill();

    void configure(int screen_width, int screen_height, int screen_width_offset);

    void render();

    void loadButtonsPanel();

    void parseClick(SDL_MouseButtonEvent& mouse_event, EventsLooperThread* processer, std::function<void(EventsLooperThread*, std::string, Point)> push_function);
};


#endif //__BUTTONS_CONTROLLER_H__
