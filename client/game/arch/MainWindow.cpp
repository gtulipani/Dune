#include "MainWindow.h"

// Commons Libraries
#include <TileUtils.h>
#include <TerrainType.h>
#include <PicturableType.h>

#define TERRAIN_RESOURCES_PATH std::string("resources/images/game/terrain")
#define UNITS_RESOURCES_PATH std::string("resources/images/game/units")

#define MAIN_WINDOW_RESOLUTION_WIDTH 1920
#define MAIN_WINDOW_RESOLUTION_HEIGHT 1080

void MainWindow::buildUnits() {
    // Store units textures
    units.emplace(LIGHT_INFANTRY, SdlTexture(UNITS_RESOURCES_PATH + "/light_infantry.png", window));
}

void MainWindow::buildTerrains() {
    // Store terrain textures
    terrains.emplace(ARENA, SdlTexture(TERRAIN_RESOURCES_PATH + "/Arena.png", window));
    terrains.emplace(CIMAS, SdlTexture(TERRAIN_RESOURCES_PATH + "/Cimas.png", window));
    terrains.emplace(DUNAS, SdlTexture(TERRAIN_RESOURCES_PATH + "/Dunas.png", window));
    terrains.emplace(ESPECIA, SdlTexture(TERRAIN_RESOURCES_PATH + "/Especia.png", window));
    terrains.emplace(PRECIPICIOS, SdlTexture(TERRAIN_RESOURCES_PATH + "/Precipicio.png", window));
    terrains.emplace(ROCA, SdlTexture(TERRAIN_RESOURCES_PATH + "/Roca.png", window));
}

void MainWindow::configure(Matrix matrix) {
    int width = MAIN_WINDOW_RESOLUTION_WIDTH;
    int height = MAIN_WINDOW_RESOLUTION_HEIGHT;
    this->matrix = std::move(matrix);
    this->window = SdlWindow(width, height, MAIN_WINDOW_RESOLUTION_WIDTH, MAIN_WINDOW_RESOLUTION_HEIGHT);
    buildTerrains();
    buildUnits();
}

void MainWindow::fill() {
    window.fill();
}

void MainWindow::render() {
    Area srcArea(0, 0, TILE_PIXEL_RATE, TILE_PIXEL_RATE);
    // Render the terrain matrix
    for (int col = 0; col < matrix.columns_quantity; col++) {
        for (int row = 0; row < matrix.rows_quantity; row++) {
            Area destArea((TILE_PIXEL_RATE * col) + offset_x, (TILE_PIXEL_RATE * row) + offset_y, TILE_PIXEL_RATE, TILE_PIXEL_RATE);
            auto it = terrains.find(matrix.at(row, col));
            if (it != terrains.end()) {
                it->second.render(srcArea, destArea);
            }
        }
    }

    // Render the SdlPicturables
    std::for_each(picturables.begin(), picturables.end(), [&](SdlPicturable &sdlPicturable) {
        sdlPicturable.render(offset_x, offset_y);
    });

    window.render();
}

void MainWindow::move(enum Movement movement) {
    switch (movement) {
        case UP: {
            offset_y -= SIZE;
            break;
        }
        case DOWN: {
            offset_y += SIZE;
            break;
        }
        case LEFT: {
            offset_x -= SIZE;
            break;
        }
        case RIGHT: {
            offset_x += SIZE;
            break;
        }

    }
}

void MainWindow::processPicturables(std::vector<Picturable> picturables) {
    std::for_each(picturables.begin(), picturables.end(), [this](Picturable &picturable) {
        auto unit_it = units.find(picturable.type);
        if (unit_it != units.end()) {
            auto picturable_it = std::find(this->picturables.begin(), this->picturables.end(), picturable);
            if (picturable_it != this->picturables.end()) {
                // Replace existing one with the new one received from the GameStatusEvent
                *picturable_it = SdlPicturable(picturable, unit_it->second);
            } else {
                // Create a new SdlPicturable
                this->picturables.emplace_back(picturable, unit_it->second);
            }
        }
    });
}
