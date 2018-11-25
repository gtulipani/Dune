#include <utility>

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

#define COMMONS_RESOURCES_PATH std::string("resources/images/game/commons/")

#define PICTURABLES_RESOURCES_SUBPATH std::string("picturables/")
#define TERRAIN_RESOURCES_SUBPATH std::string("terrain/")

TerrainController::TerrainController(SdlWindow *window, ClientSpritesSupplier &client_sprites_supplier) :
    window(window),
    client_sprites_supplier(client_sprites_supplier) {}

SdlTexture *TerrainController::createTexture(const std::string& subpath, const std::string& file_path) {
    return new SdlTexture(COMMONS_RESOURCES_PATH + subpath + file_path, this->window);
}

SdlTexture *TerrainController::createPicturableTexture(const std::string& file_path) {
    return createTexture(PICTURABLES_RESOURCES_SUBPATH, file_path);
}

SdlTexture *TerrainController::createTerrainTexture(const std::string& file_path) {
    return createTexture(TERRAIN_RESOURCES_SUBPATH, file_path);
}

void TerrainController::buildUnits() {
    // Store buildings textures
    picturables_textures_map.emplace(CONSTRUCTION_CENTER, createPicturableTexture("construction_center.png"));
    picturables_textures_map.emplace(WIND_TRAPS, createPicturableTexture("wind_traps.png"));
    picturables_textures_map.emplace(REFINERY, createPicturableTexture("refinery.png"));
    //picturables_textures_map.emplace(ATREIDES_BARRACKS, createPicturableTexture("wind_traps.png"));
    picturables_textures_map.emplace(HARKUNNAN_BARRACKS, createPicturableTexture("harkunnan_barracks.png"));
    picturables_textures_map.emplace(ORDOS_BARRACKS, createPicturableTexture("ordos_barracks.png"));
    picturables_textures_map.emplace(LIGHT_FACTORY, createPicturableTexture("light_factory.png"));
    picturables_textures_map.emplace(HEAVY_FACTORY, createPicturableTexture("heavy_factory.png"));
    picturables_textures_map.emplace(SILO, createPicturableTexture("silo.png"));
    //picturables_textures_map.emplace(PALACE, createPicturableTexture("/palace.png"));

    // Store Trike unit sprites
    picturables_textures_map.emplace(TRIKE_SPRITE_UP, createPicturableTexture("sprite_00.png"));
    picturables_textures_map.emplace(TRIKE_SPRITE_UP_RIGHT, createPicturableTexture("sprite_01.png"));
    picturables_textures_map.emplace(TRIKE_SPRITE_RIGHT, createPicturableTexture("sprite_02.png"));
    picturables_textures_map.emplace(TRIKE_SPRITE_RIGHT_DOWN, createPicturableTexture("sprite_03.png"));
    picturables_textures_map.emplace(TRIKE_SPRITE_DOWN, createPicturableTexture("sprite_04.png"));
    picturables_textures_map.emplace(TRIKE_SPRITE_DOWN_LEFT, createPicturableTexture("sprite_05.png"));
    picturables_textures_map.emplace(TRIKE_SPRITE_LEFT, createPicturableTexture("sprite_06.png"));
    picturables_textures_map.emplace(TRIKE_SPRITE_LEFT_UP, createPicturableTexture("sprite_07.png"));
}

void TerrainController::buildTerrains() {
    // Store terrain textures
    terrains_textures_map.emplace(ARENA, createTerrainTexture("Arena.png"));
    terrains_textures_map.emplace(CIMAS, createTerrainTexture("Cimas.png"));
    terrains_textures_map.emplace(DUNAS, createTerrainTexture("Dunas.png"));
    terrains_textures_map.emplace(ESPECIA, createTerrainTexture("Especia.png"));
    terrains_textures_map.emplace(PRECIPICIOS, createTerrainTexture("Precipicio.png"));
    terrains_textures_map.emplace(ROCA, createTerrainTexture("Roca.png"));
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

    this->terrain_texture = new SdlTexture(this->terrain_width, this->terrain_height, this->window->getRenderer());
    this->terrain_texture->setAsTarget();

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

    this->terrain_texture->render(srcArea, destArea);

    // Render the SdlPicturables
    std::for_each(picturables.begin(), picturables.end(), [&](SdlPicturable *sdlPicturable) {
        sdlPicturable->render(this->offset_x, this->offset_y, this->screen_width);
    });

    this->window->render();
}

void TerrainController::renderEntireTerrain(Area destArea) {
    Area srcArea(0, 0, this->terrain_width, this->terrain_height);

    this->terrain_texture->render(srcArea, destArea);
}

void TerrainController::processPicturables(std::vector<Picturable> picturables) {
    std::for_each(picturables.begin(), picturables.end(), [this](Picturable &picturable) {
        auto unit_it = picturables_textures_map.find(picturable.sprite);
        if (unit_it != picturables_textures_map.end()) {
            auto picturable_it = std::find_if(this->picturables.begin(), this->picturables.end(), [&](SdlPicturable *sdlPicturable){
                return ((*sdlPicturable) == picturable);
            });
            if (picturable_it != this->picturables.end()) {
                // Replace existing one with the new one received from the GameStatusEvent
                (*picturable_it)->update(picturable, unit_it->second);
            } else {
                // Create a new SdlPicturable
                this->picturables.push_back(new SdlPicturable(picturable, unit_it->second, this->client_sprites_supplier));
            }
        }
    });
}

Point TerrainController::getRelativePoint(int row, int column) {
    return {row - this->offset_y, column - this->offset_x};
}

void TerrainController::parseMouseClickButton(SDL_MouseButtonEvent &mouse_event) {
    this->temporary_position = getRelativePoint(mouse_event.y, mouse_event.x);
}

void TerrainController::parseMouseReleaseButton(SDL_MouseButtonEvent &mouse_event,
                                                EventsLooperThread *processer,
                                                std::function<void(EventsLooperThread *, std::string,
                                                                   Point, Point)> push_function) {
    switch (mouse_event.button) {
        case SDL_BUTTON_LEFT: {
            push_function(processer, LEFT_CLICK_TYPE, this->temporary_position, getRelativePoint(mouse_event.y, mouse_event.x));
            break;
        }
        case SDL_BUTTON_RIGHT: {
            push_function(processer, RIGHT_CLICK_TYPE, this->temporary_position, getRelativePoint(mouse_event.y, mouse_event.x));
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
        default: {
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
            auto it = terrains_textures_map.find(matrix.at(row, col));
            if (it != terrains_textures_map.end()) {
                it->second->render(srcArea, destArea);
            }
        }
    }
}

TerrainController::~TerrainController() {
    // Delete the terrain texture
    if (!this->terrain_texture) {
        delete this->terrain_texture;
    }

    // Delete all the picturables
    for (auto& picturable : this->picturables) {
        delete picturable;
    }

    // Delete all the terrain textures
    for (auto& terrain_texture : this->terrains_textures_map) {
        delete terrain_texture.second;
    }

    // Delete all the picturable textures
    for (auto& picturable_texture : this->picturables_textures_map) {
        delete picturable_texture.second;
    }
}
