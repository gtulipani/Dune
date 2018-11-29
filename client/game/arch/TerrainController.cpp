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

#define EAGLE_EYE_SQUARE_ORIGIN_WIDTH 80
#define EAGLE_EYE_SQUARE_ORIGIN_HEIGHT 80

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
    picturables_map[SPRITE_CONSTRUCTION_CENTER][SPRITE_DOWN][0] = createPicturableTexture("construction_center.png");
    picturables_map[SPRITE_WIND_TRAPS][SPRITE_DOWN][0] = createPicturableTexture("wind_traps.png");
    picturables_map[SPRITE_REFINERY][SPRITE_DOWN][0] = createPicturableTexture("refinery.png");
    //picturables_map[SPRITE_ATREIDES_BARRACKS][SPRITE_DOWN][0] = createPicturableTexture("atreides_barracks.png");
    picturables_map[SPRITE_HARKUNNAN_BARRACKS][SPRITE_DOWN][0] = createPicturableTexture("harkunnan_barracks.png");
    picturables_map[SPRITE_ORDOS_BARRACKS][SPRITE_DOWN][0] = createPicturableTexture("ordos_barracks.png");
    picturables_map[SPRITE_LIGHT_FACTORY][SPRITE_DOWN][0] = createPicturableTexture("light_factory.png");
    picturables_map[SPRITE_HEAVY_FACTORY][SPRITE_DOWN][0] = createPicturableTexture("heavy_factory.png");
    picturables_map[SPRITE_SILO][SPRITE_DOWN][0] = createPicturableTexture("silo.png");
    //picturables_map[SPRITE_PALACE][SPRITE_DOWN][0] = createPicturableTexture("palace.png");

    // Store trike sprites
    picturables_map[SPRITE_TRIKE][SPRITE_UP][0] = createPicturableTexture("trike_up.png");
    picturables_map[SPRITE_TRIKE][SPRITE_UP_RIGHT][0] = createPicturableTexture("trike_up_right.png");
    picturables_map[SPRITE_TRIKE][SPRITE_RIGHT][0] = createPicturableTexture("trike_right.png");
    picturables_map[SPRITE_TRIKE][SPRITE_DOWN_RIGHT][0] = createPicturableTexture("trike_down_right.png");
    picturables_map[SPRITE_TRIKE][SPRITE_DOWN][0] = createPicturableTexture("trike_down.png");
    picturables_map[SPRITE_TRIKE][SPRITE_DOWN_LEFT][0] = createPicturableTexture("trike_down_left.png");
    picturables_map[SPRITE_TRIKE][SPRITE_LEFT][0] = createPicturableTexture("trike_left.png");
    picturables_map[SPRITE_TRIKE][SPRITE_UP_LEFT][0] = createPicturableTexture("trike_left_up.png");

    // Store harvester sprites
    picturables_map[SPRITE_HARVESTER][SPRITE_UP][0] = createPicturableTexture("harvester_up.png");
    picturables_map[SPRITE_HARVESTER][SPRITE_UP_RIGHT][0] = createPicturableTexture("harvester_up_right.png");
    picturables_map[SPRITE_HARVESTER][SPRITE_RIGHT][0] = createPicturableTexture("harvester_right.png");
    picturables_map[SPRITE_HARVESTER][SPRITE_DOWN_RIGHT][0] = createPicturableTexture("harvester_down_right.png");
    picturables_map[SPRITE_HARVESTER][SPRITE_DOWN][0] = createPicturableTexture("harvester_down.png");
    picturables_map[SPRITE_HARVESTER][SPRITE_DOWN_LEFT][0] = createPicturableTexture("harvester_down_left.png");
    picturables_map[SPRITE_HARVESTER][SPRITE_LEFT][0] = createPicturableTexture("harvester_left.png");
    picturables_map[SPRITE_HARVESTER][SPRITE_UP_LEFT][0] = createPicturableTexture("harvester_left_up.png");

    // Store raider sprites
    picturables_map[SPRITE_RAIDER][SPRITE_UP][0] = createPicturableTexture("raider_up.png");
    picturables_map[SPRITE_RAIDER][SPRITE_UP_RIGHT][0] = createPicturableTexture("raider_up_right.png");
    picturables_map[SPRITE_RAIDER][SPRITE_RIGHT][0] = createPicturableTexture("raider_right.png");
    picturables_map[SPRITE_RAIDER][SPRITE_DOWN_RIGHT][0] = createPicturableTexture("raider_down_right.png");
    picturables_map[SPRITE_RAIDER][SPRITE_DOWN][0] = createPicturableTexture("raider_down.png");
    picturables_map[SPRITE_RAIDER][SPRITE_DOWN_LEFT][0] = createPicturableTexture("raider_down_left.png");
    picturables_map[SPRITE_RAIDER][SPRITE_LEFT][0] = createPicturableTexture("raider_left.png");
    picturables_map[SPRITE_RAIDER][SPRITE_UP_LEFT][0] = createPicturableTexture("raider_left_up.png");

    // Store tank sprites
    /*picturables_map[SPRITE_TANK][SPRITE_UP][0] = createPicturableTexture("tank_up.png");
    picturables_map[SPRITE_TANK][SPRITE_UP_RIGHT][0] = createPicturableTexture("tank_up_right.png");
    picturables_map[SPRITE_TANK][SPRITE_RIGHT][0] = createPicturableTexture("tank_right.png");
    picturables_map[SPRITE_TANK][SPRITE_DOWN_RIGHT][0] = createPicturableTexture("tank_down_right.png");
    picturables_map[SPRITE_TANK][SPRITE_DOWN][0] = createPicturableTexture("tank_down.png");
    picturables_map[SPRITE_TANK][SPRITE_DOWN_LEFT][0] = createPicturableTexture("tank_down_left.png");
    picturables_map[SPRITE_TANK][SPRITE_LEFT][0] = createPicturableTexture("tank_left.png");
    picturables_map[SPRITE_TANK][SPRITE_UP_LEFT][0] = createPicturableTexture("tank_left_up.png");

    // Store light infantry sprites
    picturables_map[SPRITE_LIGHT_INFANTRY][SPRITE_UP][0] = createPicturableTexture("light_infantry_up.png");
    picturables_map[SPRITE_LIGHT_INFANTRY][SPRITE_UP_RIGHT][0] = createPicturableTexture("light_infantry_up_right.png");
    picturables_map[SPRITE_LIGHT_INFANTRY][SPRITE_RIGHT][0] = createPicturableTexture("light_infantry_right.png");
    picturables_map[SPRITE_LIGHT_INFANTRY][SPRITE_DOWN_RIGHT][0] = createPicturableTexture("light_infantry_down_right.png");
    picturables_map[SPRITE_LIGHT_INFANTRY][SPRITE_DOWN][0] = createPicturableTexture("light_infantry_down.png");
    picturables_map[SPRITE_LIGHT_INFANTRY][SPRITE_DOWN_LEFT][0] = createPicturableTexture("light_infantry_down_left.png");
    picturables_map[SPRITE_LIGHT_INFANTRY][SPRITE_LEFT][0] = createPicturableTexture("light_infantry_left.png");
    picturables_map[SPRITE_LIGHT_INFANTRY][SPRITE_UP_LEFT][0] = createPicturableTexture("light_infantry_left_up.png");

    // Store heavy infantry sprites
    picturables_map[SPRITE_HEAVY_INFANTRY][SPRITE_UP][0] = createPicturableTexture("heavy_infantry_up.png");
    picturables_map[SPRITE_HEAVY_INFANTRY][SPRITE_UP_RIGHT][0] = createPicturableTexture("heavy_infantry_up_right.png");
    picturables_map[SPRITE_HEAVY_INFANTRY][SPRITE_RIGHT][0] = createPicturableTexture("heavy_infantry_right.png");
    picturables_map[SPRITE_HEAVY_INFANTRY][SPRITE_DOWN_RIGHT][0] = createPicturableTexture("heavy_infantry_down_right.png");
    picturables_map[SPRITE_HEAVY_INFANTRY][SPRITE_DOWN][0] = createPicturableTexture("heavy_infantry_down.png");
    picturables_map[SPRITE_HEAVY_INFANTRY][SPRITE_DOWN_LEFT][0] = createPicturableTexture("heavy_infantry_down_left.png");
    picturables_map[SPRITE_HEAVY_INFANTRY][SPRITE_LEFT][0] = createPicturableTexture("light_infantry_left.png");
    picturables_map[SPRITE_HEAVY_INFANTRY][SPRITE_UP_LEFT][0] = createPicturableTexture("light_infantry_left_up.png");*/

    // Store especia sprites
    picturables_map[SPRITE_ESPECIA][SPRITE_DOWN][0] = createPicturableTexture("especia.png");
}

void TerrainController::buildTerrains() {
    // Store terrain textures
    terrains_textures_map.emplace(ARENA, createTerrainTexture("Arena.png"));
    terrains_textures_map.emplace(CIMAS, createTerrainTexture("Cimas.png"));
    terrains_textures_map.emplace(DUNAS, createTerrainTexture("Dunas.png"));
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
    Area srcArea(0 - offset_x, 0 - offset_y, screen_width, screen_height);
    Area destArea(0, 0, screen_width, screen_height);

    terrain_texture->render(srcArea, destArea);

    // Render the SdlPicturables
    std::for_each(picturables.begin(), picturables.end(), [&](SdlPicturable *sdlPicturable) {
        sdlPicturable->render(offset_x, offset_y, screen_width);
    });

    window->render();
    pending_changes = false;
}

void TerrainController::refresh() {
    if (pending_changes) {
        render();
    }
}

void TerrainController::renderEagleEye(Area destArea) {
    Area terrainSrcArea(0, 0, this->terrain_width, this->terrain_height);
    this->terrain_texture->render(terrainSrcArea, destArea);

    Area eagleEyeSrcArea(0, 0, EAGLE_EYE_SQUARE_ORIGIN_WIDTH, EAGLE_EYE_SQUARE_ORIGIN_HEIGHT);
    // How much of the terrain is being displayed in the screen
    double view_width_rate = (static_cast<double>(destArea.getWidth()) / static_cast<double>(this->terrain_width));
    double view_height_rate = (static_cast<double>(destArea.getHeight()) / static_cast<double>(this->terrain_height));

    // Resized the offset for the eagle_eye map
    double x_offset = static_cast<double>(offset_x) * view_width_rate;
    double y_offset = static_cast<double>(offset_y) * view_height_rate;

    // Calculate the coordinates from the square
    double x_coordinate = static_cast<double>(destArea.getX()) - x_offset;
    double y_coordinate = static_cast<double>(destArea.getY()) - y_offset;

    // Recalculate the size
    double width = static_cast<double>(this->screen_width) * view_width_rate;
    double height = static_cast<double>(this->screen_height) * view_height_rate;

    Area eagleDestArea(
            static_cast<int>(x_coordinate),
            static_cast<int>(y_coordinate),
            static_cast<int>(width),
            static_cast<int>(height));
    client_sprites_supplier[EAGLE_EYE_SQUARE]->render(eagleEyeSrcArea, eagleDestArea);
}

void TerrainController::processPicturables(std::vector<Picturable>& picturables) {
    if (!picturables.empty()) {
        this->pending_changes = true;
    }

    // Update/create/delete the picturables
    std::for_each(picturables.begin(), picturables.end(), [this](Picturable &picturable) {
        // Localize texture to be rendered
        SdlTexture* texture = picturables_map[picturable.type][picturable.sprite_direction][picturable.sprite_motion];
        if (texture == nullptr) {
            std::cout << "Texture could not been found!" << std::endl;
        } else {

            auto picturable_it = std::find_if(this->picturables.begin(), this->picturables.end(),
                                              [&](SdlPicturable *sdlPicturable) {
                                                  return ((*sdlPicturable) == picturable);
                                              });
            if (picturable_it != this->picturables.end()) {
                // Replace existing one with the new one received from the GameStatusEvent
                if (picturable.health == 0) {
                    // The picturable died/was destroyed
                    delete (*picturable_it);
                    this->picturables.erase(picturable_it);
                } else {
                    (*picturable_it)->update(picturable, texture);
                }
            } else {
                // Create a new SdlPicturable
                this->picturables.push_back(new SdlPicturable(picturable, texture, this->client_sprites_supplier));
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
                                                std::function<void(EventsLooperThread *, int,
                                                                   int, Point, Point)> push_function) {
    switch (mouse_event.button) {
        case SDL_BUTTON_LEFT: {
            push_function(processer, LEFT_CLICK_EVENT_TYPE, {0}, this->temporary_position, getRelativePoint(mouse_event.y, mouse_event.x));
            break;
        }
        case SDL_BUTTON_RIGHT: {
            push_function(processer, RIGHT_CLICK_EVENT_TYPE, {0}, this->temporary_position, getRelativePoint(mouse_event.y, mouse_event.x));
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
                this->pending_changes = true;
                return true;
            }
            return false;
        }
        case DOWN: {
            if ((offset_y + this->terrain_height - this->screen_height) > 0) {
                offset_y -= TILE_PIXEL_RATE;
                this->pending_changes = true;
                return true;
            }
            return false;
        }
        case LEFT: {
            if (offset_x < 0) {
                offset_x += TILE_PIXEL_RATE;
                this->pending_changes = true;
                return true;
            }
            return false;
        }
        case RIGHT: {
            if ((offset_x + this->terrain_width - this->screen_width) > 0) {
                offset_x -= TILE_PIXEL_RATE;
                this->pending_changes = true;
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
    for (auto& unit_textures : this->picturables_map) {
        for (auto& unit_direction : unit_textures.second) {
            for (auto& unit_motion : unit_direction.second) {
                delete unit_motion.second;
            }
        }
    }
}
