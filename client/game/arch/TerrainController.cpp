#include "TerrainController.h"
#include "SdlPicturable.h"

// Commons Libraries
#include <PicturableType.h>
#include <TerrainType.h>
#include <TileUtils.h>

#define TERRAIN_RESOURCES_PATH std::string("resources/images/game/terrain")
#define UNITS_RESOURCES_PATH std::string("resources/images/game/units")

TerrainController::TerrainController(SdlWindow *window) :
    window(window) {}

void TerrainController::buildUnits() {
    // Store units textures
    units.emplace(LIGHT_INFANTRY, SdlTexture(UNITS_RESOURCES_PATH + "/light_infantry.png", window));
}

void TerrainController::buildTerrains() {
    // Store terrain textures
    terrains.emplace(ARENA, SdlTexture(TERRAIN_RESOURCES_PATH + "/Arena.png", window));
    terrains.emplace(CIMAS, SdlTexture(TERRAIN_RESOURCES_PATH + "/Cimas.png", window));
    terrains.emplace(DUNAS, SdlTexture(TERRAIN_RESOURCES_PATH + "/Dunas.png", window));
    terrains.emplace(ESPECIA, SdlTexture(TERRAIN_RESOURCES_PATH + "/Especia.png", window));
    terrains.emplace(PRECIPICIOS, SdlTexture(TERRAIN_RESOURCES_PATH + "/Precipicio.png", window));
    terrains.emplace(ROCA, SdlTexture(TERRAIN_RESOURCES_PATH + "/Roca.png", window));
}

void TerrainController::configure(Matrix matrix, int screen_width, int screen_height) {
    this->screen_width = screen_width;
    this->screen_height = screen_height;

    this->terrain_width_tiles = matrix.columns_quantity;
    this->terrain_height_tiles = matrix.rows_quantity;

    this->terrain_width = matrix.columns_quantity * TILE_PIXEL_RATE;
    this->terrain_height = matrix.rows_quantity * TILE_PIXEL_RATE;

    this->matrix = std::move(matrix);

    buildTerrains();
    buildUnits();

    this->terrain_texture = SdlTexture(this->terrain_width, this->terrain_height, this->window->getRenderer());
    this->terrain_texture.setAsTarget();

    preloadTerrainMatrix();

    this->window->render();
    this->window->setAsTarget();
}

void TerrainController::fill() {
    this->window->fill();
}

void TerrainController::render() {
    Area srcArea(0 - offset_x, 0 - offset_y, this->screen_width, this->screen_height);
    Area destArea(0, 0, this->screen_width, this->screen_height);

    this->terrain_texture.render(srcArea, destArea);

    // Render the SdlPicturables
    std::for_each(picturables.begin(), picturables.end(), [&](SdlPicturable &sdlPicturable) {
        sdlPicturable.render(this->offset_x, this->offset_y);
    });

    this->window->render();
}

void TerrainController::processPicturables(std::vector<Picturable> picturables) {
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

Point TerrainController::getRelativePoint(int row, int column) {
    return {row - this->offset_y, column - this->offset_x};
}

bool TerrainController::move(enum Movement movement) {
    switch (movement) {
        case UP: {
            if (offset_y < 0) {
                offset_y += TILE_PIXEL_RATE;
                return true;
            }
            return false;
        }
        case DOWN: {
            if ((offset_y + this->terrain_height - this->screen_height) > 0) {
                offset_y -= TILE_PIXEL_RATE;
                return true;
            }
            return false;
        }
        case LEFT: {
            if (offset_x < 0) {
                offset_x += TILE_PIXEL_RATE;
                return true;
            }
            return false;
        }
        case RIGHT: {
            if ((offset_x + this->terrain_width - this->screen_width) > 0) {
                offset_x -= TILE_PIXEL_RATE;
                return true;
            }
            return false;
        }

    }
}

void TerrainController::preloadTerrainMatrix() {
    Area srcArea(0, 0, TILE_PIXEL_RATE, TILE_PIXEL_RATE);
    // Render the terrain matrix
    for (int col = 0; col < this->terrain_width_tiles; col++) {
        for (int row = 0; row < this->terrain_height_tiles; row++) {
            Area destArea((TILE_PIXEL_RATE * col), (TILE_PIXEL_RATE * row), TILE_PIXEL_RATE, TILE_PIXEL_RATE);
            auto it = terrains.find(matrix.at(row, col));
            if (it != terrains.end()) {
                it->second.render(srcArea, destArea);
            }
        }
    }
}
