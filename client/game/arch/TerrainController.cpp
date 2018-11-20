#include "TerrainController.h"
#include "SdlPicturable.h"

// Commons Libraries
#include <TerrainType.h>
#include <TileUtils.h>
#include <Sprites.h>
#include <events/ClientEvent.h>

// SDL Libraries
#include <SDL_events.h>
#include <iostream>

#define TERRAIN_RESOURCES_PATH std::string("resources/images/game/terrain")
#define BUILDINGS_RESOURCES_PATH std::string("resources/images/game/units/buildings")
#define TRIKE_UNIT_SPRITES_RESOURCES_PATH std::string("resources/images/game/units/trike")

TerrainController::TerrainController(SdlWindow *window) :
    window(window) {}

void TerrainController::buildUnits() {
    // Store buildings textures
    picturables_textures_map.emplace(CONSTRUCTION_CENTER, SdlTexture(BUILDINGS_RESOURCES_PATH + "/construction_center.png", window));
    picturables_textures_map.emplace(WIND_TRAPS, SdlTexture(BUILDINGS_RESOURCES_PATH + "/wind_traps.png", window));
    picturables_textures_map.emplace(REFINERY, SdlTexture(BUILDINGS_RESOURCES_PATH + "/refinery.png", window));
    //picturables_textures_map.emplace(ATREIDES_BARRACKS, SdlTexture(UNITS_RESOURCES_PATH + "/wind_traps.png", window));
    picturables_textures_map.emplace(HARKUNNAN_BARRACKS, SdlTexture(BUILDINGS_RESOURCES_PATH + "/harkunnan_barracks.png", window));
    picturables_textures_map.emplace(ORDOS_BARRACKS, SdlTexture(BUILDINGS_RESOURCES_PATH + "/ordos_barracks.png", window));
    picturables_textures_map.emplace(LIGHT_FACTORY, SdlTexture(BUILDINGS_RESOURCES_PATH + "/light_factory.png", window));
    picturables_textures_map.emplace(HEAVY_FACTORY, SdlTexture(BUILDINGS_RESOURCES_PATH + "/heavy_factory.png", window));
    picturables_textures_map.emplace(SILO, SdlTexture(BUILDINGS_RESOURCES_PATH + "/silo.png", window));
    //picturables_textures_map.emplace(PALACE, SdlTexture(UNITS_RESOURCES_PATH + "/palace.png", window));

    // Store Trike unit sprites
    picturables_textures_map.emplace(TRIKE_SPRITE_UP, SdlTexture(TRIKE_UNIT_SPRITES_RESOURCES_PATH + "/sprite_00.png", window));
    picturables_textures_map.emplace(TRIKE_SPRITE_UP_RIGHT, SdlTexture(TRIKE_UNIT_SPRITES_RESOURCES_PATH + "/sprite_01.png", window));
    picturables_textures_map.emplace(TRIKE_SPRITE_RIGHT, SdlTexture(TRIKE_UNIT_SPRITES_RESOURCES_PATH + "/sprite_02.png", window));
    picturables_textures_map.emplace(TRIKE_SPRITE_RIGHT_DOWN, SdlTexture(TRIKE_UNIT_SPRITES_RESOURCES_PATH + "/sprite_03.png", window));
    picturables_textures_map.emplace(TRIKE_SPRITE_DOWN, SdlTexture(TRIKE_UNIT_SPRITES_RESOURCES_PATH + "/sprite_04.png", window));
    picturables_textures_map.emplace(TRIKE_SPRITE_DOWN_LEFT, SdlTexture(TRIKE_UNIT_SPRITES_RESOURCES_PATH + "/sprite_05.png", window));
    picturables_textures_map.emplace(TRIKE_SPRITE_LEFT, SdlTexture(TRIKE_UNIT_SPRITES_RESOURCES_PATH + "/sprite_06.png", window));
    picturables_textures_map.emplace(TRIKE_SPRITE_LEFT_UP, SdlTexture(TRIKE_UNIT_SPRITES_RESOURCES_PATH + "/sprite_07.png", window));
}

void TerrainController::buildTerrains() {
    // Store terrain textures
    terrains_textures_map.emplace(ARENA, SdlTexture(TERRAIN_RESOURCES_PATH + "/Arena.png", window));
    terrains_textures_map.emplace(CIMAS, SdlTexture(TERRAIN_RESOURCES_PATH + "/Cimas.png", window));
    terrains_textures_map.emplace(DUNAS, SdlTexture(TERRAIN_RESOURCES_PATH + "/Dunas.png", window));
    terrains_textures_map.emplace(ESPECIA, SdlTexture(TERRAIN_RESOURCES_PATH + "/Especia.png", window));
    terrains_textures_map.emplace(PRECIPICIOS, SdlTexture(TERRAIN_RESOURCES_PATH + "/Precipicio.png", window));
    terrains_textures_map.emplace(ROCA, SdlTexture(TERRAIN_RESOURCES_PATH + "/Roca.png", window));
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
        auto unit_it = picturables_textures_map.find(picturable.sprite);
        if (unit_it != picturables_textures_map.end()) {
            auto picturable_it = std::find(this->picturables.begin(), this->picturables.end(), picturable);
            if (picturable_it != this->picturables.end()) {
                // Replace existing one with the new one received from the GameStatusEvent
                this->picturables.erase(picturable_it);
                this->picturables.emplace_back(picturable, unit_it->second);
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

void TerrainController::parseClick(SDL_MouseButtonEvent& mouse_event,
                                   EventsLooperThread* processer,
                                   std::function<void(EventsLooperThread*, std::string, Point)> push_function) {
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
    return false; // For g++ warning
}

void TerrainController::preloadTerrainMatrix() {
    Area srcArea(0, 0, TILE_PIXEL_RATE, TILE_PIXEL_RATE);
    // Render the terrain matrix
    for (int col = 0; col < this->terrain_width_tiles; col++) {
        for (int row = 0; row < this->terrain_height_tiles; row++) {
            Area destArea((TILE_PIXEL_RATE * col), (TILE_PIXEL_RATE * row), TILE_PIXEL_RATE, TILE_PIXEL_RATE);
            auto it = terrains_textures_map.find(matrix.at(row, col));
            if (it != terrains_textures_map.end()) {
                it->second.render(srcArea, destArea);
            }
        }
    }
}
