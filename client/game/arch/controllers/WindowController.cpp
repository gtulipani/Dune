#include <utility>

#include "WindowController.h"

// Commons Libraries
#include <TileUtils.h>
#include <TerrainType.h>
#include <events/GameStatusEvent.h>

// Client Libraries
#include "RequiresExternalControllerActionException.h"
#include "../ScreenInformation.h"

// SDL Libraries
#include <SDL_events.h>

#define WINDOW_WIDTH 1280
#define WINDOW_HEIGHT 720

WindowController::WindowController(SdlWindow* window, const ScreenConfiguration& screen_configuration, const Matrix& matrix) : Controller(
        window,
        screen_configuration,
        true),
        client_sprites_supplier(window),
        pending_action(false) {
    buildControllers(matrix);
}

WindowController::WindowController(const Matrix& matrix) : WindowController(
        new SdlWindow(WINDOW_WIDTH, WINDOW_HEIGHT, SCREEN_WIDTH, SCREEN_HEIGHT),
        ScreenConfiguration(SCREEN_WIDTH, SCREEN_HEIGHT, 0, 0),
        matrix) {}

void WindowController::buildControllers(const Matrix& matrix) {
    controllers.push_back(new ButtonsController(window, client_sprites_supplier, screen_manager, ScreenConfiguration(SCREEN_PANEL_WIDTH, SCREEN_PANEL_HEIGHT, SCREEN_TERRAIN_WIDTH, 0)));
    controllers.push_back(new TerrainController(window, client_sprites_supplier, screen_manager, ScreenConfiguration(SCREEN_TERRAIN_WIDTH, SCREEN_TERRAIN_HEIGHT, 0, SCREEN_STATUS_HEIGHT), matrix));
    controllers.push_back(new StatusController(window, client_sprites_supplier, ScreenConfiguration(SCREEN_STATUS_WIDTH, SCREEN_STATUS_HEIGHT, 0, 0)));
}

void WindowController::render() {
    std::for_each(controllers.begin(), controllers.end(), [](Controller* controller) {
        controller->refresh();
    });
}

void WindowController::move(enum Movement movement) {
    std::for_each(controllers.begin(), controllers.end(), [movement](Controller* controller) {
        controller->move(movement);
    });
}

bool WindowController::resolvePendingAction(const SDL_MouseButtonEvent &mouse_event, EventsLooperThread *processer, const std::function<void(EventsLooperThread *, int, int, Point, Point)>& push_function) {
    return false;
}

void WindowController::parseMouseClick(const SDL_MouseButtonEvent& mouse_event, EventsLooperThread* processer, const std::function<void(EventsLooperThread*, int, int, Point, Point)>& push_function) {
    std::for_each(controllers.begin(), controllers.end(), [mouse_event, processer, push_function](Controller* controller) {
        controller->parseMouseClick(mouse_event, processer, push_function);
    });
}

void WindowController::parseMouseRelease(const SDL_MouseButtonEvent& mouse_event, EventsLooperThread* processer, const std::function<void(EventsLooperThread*, int, int, Point, Point)>& push_function) {
    if (pending_action) {
        bool action_happened = false;
        std::for_each(controllers.begin(), controllers.end(), [&action_happened, mouse_event, processer, push_function](Controller* controller) {
            // We set action_happened as true if any of the controllers resolved an action
            action_happened = (action_happened || controller->resolvePendingAction(mouse_event, processer, push_function));
        });
        if (action_happened) {
            // If at least one controller resolved a pending action
            pending_action = false;
        }
    } else {
        try {
            std::for_each(controllers.begin(), controllers.end(), [mouse_event, processer, push_function](Controller* controller) {
                controller->parseMouseRelease(mouse_event, processer, push_function);
            });
        } catch (RequiresExternalControllerActionException& e) {
            // Action in another controller is required
            pending_action = true;
        }
    }
}

void WindowController::update(const GameStatusEvent &event) {
    std::for_each(controllers.begin(), controllers.end(), [event](Controller* controller) {
        controller->update(event);
    });
}

WindowController::~WindowController() {
    // Delete controllers
    for (auto &controller : controllers) {
        delete controller;
    }
}
