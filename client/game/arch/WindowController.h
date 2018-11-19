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

class SDL_MouseButtonEvent;
class EventsLooperThread;

class WindowController {
private:
    SdlWindow window{};
    TerrainController terrain_controller;
    ButtonsController buttons_controller;

    // Shouldn't be used. It's moved to the terrain_controller
    Matrix matrix;
public:
    WindowController();

    WindowController(const WindowController &other) = delete;

    // Overloading the assignment by copy
    WindowController &operator=(const WindowController &other) = delete;

    void configure(Matrix matrix);

    void fill();

    void render();

    void move(enum Movement movement);

    void parseClick(SDL_MouseButtonEvent& mouse_event, EventsLooperThread* processer, std::function<void(EventsLooperThread*, std::string, Point)> push_function);

    void processPicturables(std::vector<Picturable> picturables);

    Point getRelativePoint(int row, int column);
};


#endif //__WINDOW_CONTROLLER_H__
