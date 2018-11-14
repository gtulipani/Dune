#include "MainWindow.h"

// Commons Libraries
#include <TileUtils.h>
#include <TerrainType.h>
#include <PicturableType.h>

#define TERRAIN_RESOURCES_PATH std::string("resources/images/game/terrain")
#define UNITS_RESOURCES_PATH std::string("resources/images/game/units")

#define MAIN_WINDOW_WIDTH 1280
#define MAIN_WINDOW_HEIGHT 720
#define MAIN_WINDOW_RESOLUTION_WIDTH 800
#define MAIN_WINDOW_RESOLUTION_HEIGHT 600

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
    this->width = matrix.columns_quantity * TILE_PIXEL_RATE;
    this->height = matrix.rows_quantity * TILE_PIXEL_RATE;
    this->rows_quantity = matrix.rows_quantity;
    this->columns_quantity = matrix.columns_quantity;
    this->matrix = std::move(matrix);

    this->window = SdlWindow(MAIN_WINDOW_WIDTH, MAIN_WINDOW_HEIGHT, MAIN_WINDOW_RESOLUTION_WIDTH, MAIN_WINDOW_RESOLUTION_HEIGHT);
    this->window.fill();

    buildTerrains();
    buildUnits();

    this->terrain_texture = SdlTexture(width, height, this->window.getRenderer());
    this->terrain_texture.setAsTarget();

    preloadTerrainMatrix();

    this->window.render();
    this->window.setAsTarget();
}

void MainWindow::fill() {
    window.fill();
}

void MainWindow::preloadTerrainMatrix() {
    Area srcArea(0, 0, TILE_PIXEL_RATE, TILE_PIXEL_RATE);
    // Render the terrain matrix
    for (int col = 0; col < this->columns_quantity; col++) {
        for (int row = 0; row < this->rows_quantity; row++) {
            Area destArea((TILE_PIXEL_RATE * col), (TILE_PIXEL_RATE * row), TILE_PIXEL_RATE, TILE_PIXEL_RATE);
            auto it = terrains.find(matrix.at(row, col));
            if (it != terrains.end()) {
                it->second.render(srcArea, destArea);
            }
        }
    }
}

void MainWindow::render() {
    Area srcArea(0, 0, this->width, this->height);
    Area destArea(offset_x, offset_y, this->width, this->height);
    this->terrain_texture.render(srcArea, destArea);

    // Render the SdlPicturables
    std::for_each(picturables.begin(), picturables.end(), [&](SdlPicturable &sdlPicturable) {
        sdlPicturable.render(offset_x, offset_y);
    });

    window.render();
}

void MainWindow::move(enum Movement movement) {
    switch (movement) {
        case UP: {
            if (offset_y < 0) {
                offset_y += TILE_PIXEL_RATE;
            }
            break;
        }
        case DOWN: {
            if ((offset_y + this->height - MAIN_WINDOW_RESOLUTION_HEIGHT) > 0) {
                offset_y -= TILE_PIXEL_RATE;
            }
            break;
        }
        case LEFT: {
            if (offset_x < 0) {
                offset_x += TILE_PIXEL_RATE;
            }
            break;
        }
        case RIGHT: {
            if ((offset_x + this->width - MAIN_WINDOW_RESOLUTION_WIDTH) > 0) {
                offset_x -= TILE_PIXEL_RATE;
            }
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

Point MainWindow::getRelativePoint(int row, int column) {
    return {row - offset_y, column - offset_x};
}
