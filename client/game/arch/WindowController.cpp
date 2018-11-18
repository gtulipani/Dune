#include "WindowController.h"

// Commons Libraries
#include <TileUtils.h>
#include <TerrainType.h>
#include <PicturableType.h>

#define MAIN_WINDOW_WIDTH 1280
#define MAIN_WINDOW_HEIGHT 720

WindowController::WindowController() :
    window(MAIN_WINDOW_WIDTH, MAIN_WINDOW_HEIGHT, MAIN_WINDOW_RESOLUTION_WIDTH, MAIN_WINDOW_RESOLUTION_HEIGHT),
    terrain_controller(&this->window),
    buttons_controller(&this->window) {}

void WindowController::configure(Matrix matrix) {
    this->window.fill();

    this->terrain_controller.configure(std::move(matrix));
}

void WindowController::fill() {
    this->terrain_controller.fill();
}

void WindowController::render() {
    this->terrain_controller.render();
}

void WindowController::move(enum Movement movement) {
    this->terrain_controller.move(movement);
}

void WindowController::processPicturables(std::vector<Picturable> picturables) {
    this->terrain_controller.processPicturables(std::move(picturables));
}

Point WindowController::getRelativePoint(int row, int column) {
    return this->terrain_controller.getRelativePoint(row, column);
}
