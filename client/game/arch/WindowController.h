#ifndef __WINDOW_CONTROLLER_H__
#define __WINDOW_CONTROLLER_H__

// STL Libraries
#include <functional>

// Commons Libraries
#include <Matrix.h>

// Client Libraries
#include "../sdl/SdlWindow.h"
#include "../sdl/SdlTexture.h"
#include "SdlPicturable.h"
#include "TerrainController.h"
#include "ButtonsController.h"

typedef enum Controller {
    TERRAIN,
    BUTTONS,
    NONE
} Controller;

class SDL_MouseButtonEvent;
class EventsLooperThread;

class WindowController {
private:
    SdlWindow* window;
    ClientSpritesSupplier client_sprites_supplier;
    TerrainController terrain_controller;
    ButtonsController buttons_controller;

    // Shouldn't be used. It's moved to the terrain_controller
    Matrix matrix;

    enum Controller last_click_event_occurrence = NONE;
public:
    WindowController(SdlWindow* window);

    WindowController();

    WindowController(const WindowController &other) = delete;

    // Overloading the assignment by copy
    WindowController &operator=(const WindowController &other) = delete;

    void configure(Matrix matrix);

    void fill();

    void refreshMap();

    void render();

    bool move(enum Movement movement);

    void parseMouseClick(SDL_MouseButtonEvent& mouse_event, EventsLooperThread* processer, std::function<void(EventsLooperThread*, std::string, Point, Point)> push_function);
    void parseMouseRelease(SDL_MouseButtonEvent& mouse_event, EventsLooperThread* processer, std::function<void(EventsLooperThread*, std::string, Point, Point)> push_function);

    void processPicturables(std::vector<Picturable> picturables);

    ~WindowController() {}
};


#endif //__WINDOW_CONTROLLER_H__
