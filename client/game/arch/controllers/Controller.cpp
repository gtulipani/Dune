#include "Controller.h"

// Client Libraries
#include "../../sdl/SdlWindow.h"

Controller::Controller(unsigned int player_id, SdlWindow *window, const ScreenConfiguration& screen_configuration, bool pending_changes) :
        player_id(player_id),
        window(window),
        screen_configuration(screen_configuration),
        pending_changes(pending_changes) {}

bool Controller::notIncludes(int x, int y) {
    int x_begin = screen_configuration.getWidthOffset();
    int x_end = x_begin + screen_configuration.getWidth();
    int y_begin = screen_configuration.getHeightOffset();
    int y_end = y_begin + screen_configuration.getHeight();

    return (x <= x_begin || x >= x_end || y <= y_begin || y >= y_end);
}

bool Controller::includes(int x, int y) {
    int x_begin = screen_configuration.getWidthOffset();
    int x_end = x_begin + screen_configuration.getWidth();
    int y_begin = screen_configuration.getHeightOffset();
    int y_end = y_begin + screen_configuration.getHeight();

    return (x >= x_begin && x <= x_end && y >= y_begin && y <= y_end);
}

void Controller::fill() {
    window->fill();
}

void Controller::refresh() {
    if (pending_changes) {
        render();
    }
}

Controller::~Controller() = default;
