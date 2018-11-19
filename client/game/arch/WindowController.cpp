#include "WindowController.h"

// Commons Libraries
#include <TileUtils.h>
#include <TerrainType.h>
#include <PicturableType.h>
#include <SDL_events.h>
#include <events/ClientEvent.h>

#define WINDOW_WIDTH 1280
#define WINDOW_HEIGHT 720

#define TERRAIN_WIDTH 880
#define TERRAIN_HEIGHT 720

#define PANEL_WIDTH 400
#define PANEL_HEIGHT 720

#define TERRAIN_CONTROLLER_RATE 0.8
#define BUTTONS_CONTROLLER_RATE 0.2

WindowController::WindowController() :
    window(WINDOW_WIDTH, WINDOW_HEIGHT, MAIN_WINDOW_RESOLUTION_WIDTH, MAIN_WINDOW_RESOLUTION_HEIGHT),
    terrain_controller(&this->window, TERRAIN_CONTROLLER_RATE),
    buttons_controller(&this->window) {}

void WindowController::configure(Matrix matrix) {
    this->window.fill();

    this->terrain_controller.configure(std::move(matrix));
    this->buttons_controller.configure(PANEL_WIDTH, PANEL_HEIGHT, TERRAIN_WIDTH, TERRAIN_HEIGHT);
}

void WindowController::fill() {
    this->terrain_controller.fill();
    this->buttons_controller.fill();
}

void WindowController::render() {
    //this->terrain_controller.render();
    this->buttons_controller.render();
}

void WindowController::move(enum Movement movement) {
    this->terrain_controller.move(movement);
}

void WindowController::parseClick(SDL_MouseButtonEvent& mouse_event, EventsLooperThread* processer, std::function<void(EventsLooperThread*, std::string, Point)> push_function) {
    switch (mouse_event.button) {
        case SDL_BUTTON_LEFT: {
            push_function(processer, LEFT_CLICK_TYPE, getRelativePoint(mouse_event.y, mouse_event.x));
            break;
        }
        case SDL_BUTTON_RIGHT: {
            push_function(processer, RIGHT_CLICK_TYPE, getRelativePoint(mouse_event.y, mouse_event.x));
            break;
        }
        default:
            break;
    }
}

void WindowController::processPicturables(std::vector<Picturable> picturables) {
    this->terrain_controller.processPicturables(std::move(picturables));
}

Point WindowController::getRelativePoint(int row, int column) {
    return this->terrain_controller.getRelativePoint(row, column);
}
