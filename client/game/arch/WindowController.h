#ifndef __MAIN_WINDOW_H__
#define __MAIN_WINDOW_H__

// Commons Libraries
#include <Matrix.h>

// Client Libraries
#include "../sdl/SdlWindow.h"
#include "../sdl/SdlTexture.h"
#include "SdlPicturable.h"
#include "TerrainController.h"
#include "ButtonsController.h"

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

    void processPicturables(std::vector<Picturable> picturables);

    Point getRelativePoint(int row, int column);
};


#endif //__MAIN_WINDOW_H__
