#ifndef __WINDOW_CONTROLLER_H__
#define __WINDOW_CONTROLLER_H__

// STL Libraries
#include <functional>

// Commons Libraries
#include <Matrix.h>

// Client Libraries
#include "../../sdl/SdlWindow.h"
#include "../../sdl/SdlTexture.h"
#include "../SdlPicturable.h"
#include "../ScreenInformation.h"
#include "ButtonsController.h"
#include "TerrainController.h"
#include "StatusController.h"
#include "Controller.h"

class WindowController : public Controller {
private:
    std::vector<Controller*> controllers;
    ClientSpritesSupplier client_sprites_supplier;
    ScreenInformation screen_manager{};

    bool pending_action;

    void buildControllers(const Matrix& matrix);
public:
    WindowController(unsigned int player_id, SdlWindow* window, const ScreenConfiguration& screen_configuration, const Matrix& matrix);

    explicit WindowController(unsigned int player_id, const Matrix& matrix);

    WindowController(const WindowController &other) = delete;

    // Overloading the assignment by copy
    WindowController &operator=(const WindowController &other) = delete;

    void update(const GameStatusEvent &event) override;

    void render() override;

    void move(enum Movement movement) override;

    bool resolvePendingAction(const SDL_MouseButtonEvent &mouse_event, EventsLooperThread *processer, const std::function<void(EventsLooperThread *, int, int, Point, Point)>& push_function) override;
    void parseMouseClick(const SDL_MouseButtonEvent& mouse_event, EventsLooperThread* processer, const std::function<void(EventsLooperThread*, int, int, Point, Point)>& push_function) override;
    void parseMouseRelease(const SDL_MouseButtonEvent& mouse_event, EventsLooperThread* processer, const std::function<void(EventsLooperThread*, int, int, Point, Point)>& push_function) override;

    ~WindowController() override;
};


#endif //__WINDOW_CONTROLLER_H__
