#ifndef __STATUS_CONTROLLER_H__
#define __STATUS_CONTROLLER_H__

// Client Libraries
#include "../../sdl/SdlWindow.h"
#include "../ClientSpritesSupplier.h"

class StatusController {
private:
    SdlWindow* window;
    ClientSpritesSupplier &client_sprites_supplier;

public:
    StatusController(SdlWindow *window, ClientSpritesSupplier &client_sprites_supplier);
};


#endif //__STATUS_CONTROLLER_H__
