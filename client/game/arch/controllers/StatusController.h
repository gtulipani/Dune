#ifndef __STATUS_CONTROLLER_H__
#define __STATUS_CONTROLLER_H__

// STL Libraries
#include <functional>

// Client Libraries
#include "../../sdl/SdlWindow.h"
#include "../ClientSpritesSupplier.h"
#include "../ScreenConfiguration.h"
#include "Controller.h"

// SDL Libraries
#include <SDL2/SDL_pixels.h>
#include <SDL2/SDL_ttf.h>

class SdlText;
class Point;

class StatusController : public Controller {
private:
    ClientSpritesSupplier &client_sprites_supplier;
    TTF_Font* font;
    SDL_Color color;
    int energy;
    int especia;
    SdlText* energy_text;
    SdlText* especia_text;

    TTF_Font *buildFont();
public:
    StatusController(SdlWindow *window, ClientSpritesSupplier &client_sprites_supplier, const ScreenConfiguration& screen_configuration, TTF_Font* font);

    StatusController(SdlWindow *window, ClientSpritesSupplier &client_sprites_supplier, const ScreenConfiguration& screen_configuration);

    void update(const GameStatusEvent &event) override;

    void render() override;

    void move(enum Movement movement) override;

    bool resolvePendingAction(const SDL_MouseButtonEvent &mouse_event, EventsLooperThread *processer, const std::function<void(EventsLooperThread *, int, int, Point, Point)>& push_function) override;
    void parseMouseClick(const SDL_MouseButtonEvent& mouse_event, EventsLooperThread* processer, const std::function<void(EventsLooperThread*, int, int, Point, Point)>& push_function) override;
    void parseMouseRelease(const SDL_MouseButtonEvent &mouse_event, EventsLooperThread *processer, const std::function<void(EventsLooperThread *, int, int, Point, Point)>& push_function) override;

    ~StatusController() override;
};


#endif //__STATUS_CONTROLLER_H__
