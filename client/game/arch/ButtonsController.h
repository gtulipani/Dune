#ifndef __BUTTONS_CONTROLLER_H__
#define __BUTTONS_CONTROLLER_H__

// Client Libraries
#include "../sdl/SdlWindow.h"

class ButtonsController {
private:
    int width{};
    int height{};
    SdlWindow *window;

public:
    explicit ButtonsController(SdlWindow *window);
};


#endif //__BUTTONS_CONTROLLER_H__
