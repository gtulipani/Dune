#ifndef __STATUS_CONTROLLER_H__
#define __STATUS_CONTROLLER_H__

// Client Libraries
#include "../../sdl/SdlWindow.h"
#include "../ClientSpritesSupplier.h"

// SDL Libraries
#include <SDL2/SDL_pixels.h>
#include <SDL2/SDL_ttf.h>

class GameStatusEvent;
class SdlText;

class StatusController {
private:
    SdlWindow* window;
    ClientSpritesSupplier &client_sprites_supplier;
    TTF_Font* font;
    SDL_Color color;
    int energy;
    int especia;
    bool pending_changes;

    int screen_width{};
    int screen_height{};

    SdlText* energy_text;
    SdlText* especia_text;

    TTF_Font *buildFont();
public:
    StatusController(SdlWindow *window, ClientSpritesSupplier &client_sprites_supplier, TTF_Font* font);

    StatusController(SdlWindow *window, ClientSpritesSupplier &client_sprites_supplier);

    void configure(int screen_width, int screen_height);

    void render();

    void refresh();

    void update(const GameStatusEvent &event);

    ~StatusController();
};


#endif //__STATUS_CONTROLLER_H__
