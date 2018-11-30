#include "StatusController.h"

StatusController::StatusController(SdlWindow *window, ClientSpritesSupplier &client_sprites_supplier) :
        window(window),
        client_sprites_supplier(client_sprites_supplier) {}