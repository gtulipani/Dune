#include <utility>

#include "WindowController.h"

// Commons Libraries
#include <TileUtils.h>
#include <TerrainType.h>

// SDL Libraries
#include <SDL_events.h>

#define WINDOW_WIDTH 1280
#define WINDOW_HEIGHT 720

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600

#define SCREEN_TERRAIN_RATE 0.75
#define SCREEN_BUTTONS_RATE 0.25

#define SCREEN_TERRAIN_WIDTH int(SCREEN_WIDTH * SCREEN_TERRAIN_RATE)
#define SCREEN_PANEL_WIDTH int(SCREEN_WIDTH * SCREEN_BUTTONS_RATE)

WindowController::WindowController(SdlWindow* window) :
    window(window),
    client_sprites_supplier(window),
    terrain_controller(window, client_sprites_supplier),
    buttons_controller(window, client_sprites_supplier) {}

WindowController::WindowController() : WindowController(
        new SdlWindow(WINDOW_WIDTH, WINDOW_HEIGHT, SCREEN_WIDTH, SCREEN_HEIGHT)) {}

void WindowController::configure(Matrix matrix) {
    this->window->fill();

    this->terrain_controller.configure(std::move(matrix), SCREEN_TERRAIN_WIDTH, SCREEN_HEIGHT);
    this->buttons_controller.configure(SCREEN_PANEL_WIDTH, SCREEN_HEIGHT, SCREEN_TERRAIN_WIDTH);
}

void WindowController::fill() {
    this->terrain_controller.fill();
    this->buttons_controller.fill();
}

void WindowController::refreshMap() {
    this->terrain_controller.render();
}

void WindowController::render() {
    this->terrain_controller.render();
    this->buttons_controller.render(&this->terrain_controller, &TerrainController::renderEntireTerrain);
}

bool WindowController::move(enum Movement movement) {
    return this->terrain_controller.move(movement);
}

void WindowController::parseMouseClick(SDL_MouseButtonEvent& mouse_event, EventsLooperThread* processer, std::function<void(EventsLooperThread*, std::string, Point, Point)> push_function) {
    if (mouse_event.x < SCREEN_TERRAIN_WIDTH) {
        terrain_controller.parseMouseClickButton(mouse_event);
        // Store where does the Mouse Click take place
        last_click_event_occurrence = TERRAIN;
    } else {
        buttons_controller.parseClick(mouse_event, processer, std::move(push_function));
        // Store where does the Mouse Click take place
        last_click_event_occurrence = BUTTONS;
    }
}

void WindowController::parseMouseRelease(SDL_MouseButtonEvent& mouse_event, EventsLooperThread* processer, std::function<void(EventsLooperThread*, std::string, Point, Point)> push_function) {
    if (mouse_event.x < SCREEN_TERRAIN_WIDTH) {
        if (last_click_event_occurrence == BUTTONS) {
            // We clicked on the Panel Section and we released the mouse on the terrain section. Don't do anything
            return;
        } else {
            terrain_controller.parseMouseReleaseButton(mouse_event, processer, std::move(push_function));
        }
    } else {
        if (last_click_event_occurrence == TERRAIN) {
            // We clicked on the Terrain Section and we released the mouse on the buttons section. Don't do anything
            return;
        } else {
            buttons_controller.parseClick(mouse_event, processer, std::move(push_function));
        }
    }
    last_click_event_occurrence = NONE;
}

void WindowController::processPicturables(std::vector<Picturable> picturables) {
    this->terrain_controller.processPicturables(std::move(picturables));
}
