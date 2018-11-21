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
    terrain_controller(window),
    buttons_controller(window) {}

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
    this->buttons_controller.render();
}

bool WindowController::move(enum Movement movement) {
    return this->terrain_controller.move(movement);
}

void WindowController::parseClick(SDL_MouseButtonEvent& mouse_event, EventsLooperThread* processer, std::function<void(EventsLooperThread*, std::string, Point)> push_function) {
    if (mouse_event.x < SCREEN_TERRAIN_WIDTH) {
        terrain_controller.parseClick(mouse_event, processer, std::move(push_function));
    } else {
        buttons_controller.parseClick(mouse_event, processer, std::move(push_function));
    }
}

void WindowController::processPicturables(std::vector<Picturable> picturables) {
    this->terrain_controller.processPicturables(std::move(picturables));
}

Point WindowController::getRelativePoint(int row, int column) {
    return this->terrain_controller.getRelativePoint(row, column);
}
