#include "TerrainController.h"

// STL Libraries
#include <iostream>
#include <utility>

// Commons Libraries
#include <TerrainType.h>
#include <TileUtils.h>
#include <Sprites.h>
#include <UnitsAndBuildings.h>
#include <events/ClientEvent.h>
#include <events/GameStatusEvent.h>

// Client Libraries
#include "../ClientPicturable.h"
#include "../ScreenInformation.h"

// SDL Libraries
#include <SDL_events.h>

#define COMMONS_RESOURCES_PATH std::string("resources/images/game/commons/")

#define PICTURABLES_RESOURCES_SUBPATH std::string("picturables/")
#define TERRAIN_RESOURCES_SUBPATH std::string("terrain/")

#define EAGLE_EYE_SQUARE_ORIGIN_WIDTH 80
#define EAGLE_EYE_SQUARE_ORIGIN_HEIGHT 80

#define PICTURABLE_FILE_DIRECTION_MOTION_SEPARATOR "_"
#define PICTURABLE_FILE_EXTENSION ".png"

TerrainController::TerrainController(int player_id, SdlWindow *window, ClientSpritesSupplier &client_sprites_supplier, ScreenInformation &screen_manager, const ScreenConfiguration& screen_configuration, const Matrix& matrix) : Controller(
        player_id,
        window,
        screen_configuration,
        true),
        client_sprites_supplier(client_sprites_supplier),
        screen_information(screen_manager),
        matrix(matrix),
        terrain_width_tiles(matrix.columns_quantity),
        terrain_height_tiles(matrix.rows_quantity),
        terrain_width(matrix.columns_quantity * TILE_PIXEL_RATE),
        terrain_height(matrix.rows_quantity * TILE_PIXEL_RATE),
        clicked(false) {
    buildTerrains();
    buildPicturables();
    buildTerrainTexture();
}

void TerrainController::buildTerrains() {
    // Store terrain textures
    terrains_textures_map.emplace(ARENA, createTerrainTexture("Arena.png"));
    terrains_textures_map.emplace(CIMAS, createTerrainTexture("Cimas.png"));
    terrains_textures_map.emplace(DUNAS, createTerrainTexture("Dunas.png"));
    terrains_textures_map.emplace(PRECIPICIOS, createTerrainTexture("Precipicio.png"));
    terrains_textures_map.emplace(ROCA, createTerrainTexture("Roca.png"));
}


void TerrainController::buildBuilding(const std::string &building_name, enum PlayerColor player_color, SdlColor *color) {
    picturables_map[building_name][SPRITE_DOWN][0][player_color] = createPicturableTexture("construction_center.png", color);
}

void TerrainController::buildVehicle(const std::string &vehicle_name, enum PlayerColor player_color, SdlColor *color) {
    // Iterate over the available directions
    for (int dir = SPRITE_UP; dir <= SPRITE_UP_LEFT; dir++) {
        auto direction = static_cast<Direction>(dir);
        picturables_map[vehicle_name][direction][0][player_color] = createPicturableTexture(
                vehicle_name +
                PICTURABLE_FILE_DIRECTION_MOTION_SEPARATOR +
                std::to_string(dir) +
                PICTURABLE_FILE_EXTENSION, color);
    }
}

void TerrainController::buildUnit(const std::string &unit_name, enum PlayerColor player_color, SdlColor *color) {
    // Iterate over the available directions
    for (int dir = SPRITE_UP; dir <= SPRITE_UP_LEFT; dir++) {
        auto direction = static_cast<Direction>(dir);
        // Iterate over the available motion
        for (int motion = 0; motion <= MAX_MOTION; motion++) {
            picturables_map[unit_name][direction][motion][player_color] = createPicturableTexture(
                    unit_name +
                    PICTURABLE_FILE_DIRECTION_MOTION_SEPARATOR +
                    std::to_string(dir) +
                    PICTURABLE_FILE_DIRECTION_MOTION_SEPARATOR +
                    std::to_string(motion) +
                    PICTURABLE_FILE_EXTENSION, color);
        }
    }
}

void TerrainController::buildPicturablesForColor(enum PlayerColor player_color) {
    SdlColor *color = player_color::getColor(player_color);
    if (color != nullptr) {
        // Store buildings textures
        buildBuilding(CONSTRUCTION_CENTER, player_color, color);
        buildBuilding(WIND_TRAPS, player_color, color);
        buildBuilding(REFINERY, player_color, color);
        buildBuilding(BARRACKS, player_color, color);
        buildBuilding(LIGHT_FACTORY, player_color, color);
        buildBuilding(HEAVY_FACTORY, player_color, color);
        buildBuilding(SILO, player_color, color);

        buildVehicle(TRIKE, player_color, color);
        buildVehicle(RAIDER, player_color, color);
        buildVehicle(TANK, player_color, color);
        buildVehicle(HARVESTER, player_color, color);

        buildUnit(LIGHT_INFANTRY, player_color, color);
        buildUnit(HEAVY_INFANTRY, player_color, color);

        delete color;
    }
}
void TerrainController::buildEspecia() {
    // Store especia sprites. We don't apply any color on it
    picturables_map[ESPECIA][SPRITE_DOWN][0][NO_PLAYER] = createPicturableTexture("especia_100.png");
    picturables_map[ESPECIA][SPRITE_DOWN][1][NO_PLAYER] = createPicturableTexture("especia_80.png");
    picturables_map[ESPECIA][SPRITE_DOWN][2][NO_PLAYER] = createPicturableTexture("especia_60.png");
    picturables_map[ESPECIA][SPRITE_DOWN][3][NO_PLAYER] = createPicturableTexture("especia_40.png");
    picturables_map[ESPECIA][SPRITE_DOWN][4][NO_PLAYER] = createPicturableTexture("especia_20.png");
}

void TerrainController::buildPicturables() {
    // Iterate over the available colors
    for (int color = RED; color != YELLOW; color++) {
        auto player_color = static_cast<PlayerColor>(color);
        buildPicturablesForColor(player_color);
    }
    buildEspecia();
}

void TerrainController::buildTerrainTexture() {
    this->terrain_texture = new SdlTexture(this->terrain_width, this->terrain_height, this->window->getRenderer());
    this->terrain_texture->setAsTarget();

    preloadTerrainMatrix();

    this->window->render();
    this->window->setAsTarget();
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

SdlTexture *TerrainController::createTexture(const std::string& subpath, const std::string& file_path) {
    return new SdlTexture(COMMONS_RESOURCES_PATH + subpath + file_path, this->window);
}

SdlTexture *TerrainController::createPicturableTexture(const std::string& file_path) {
    return createTexture(PICTURABLES_RESOURCES_SUBPATH, file_path);
}

SdlTexture *TerrainController::createPicturableTexture(const std::string& file_path, SdlColor *color) {
    SdlTexture * texture = createPicturableTexture(file_path);
    texture->setColor(color);
    return texture;
}

SdlTexture *TerrainController::createTerrainTexture(const std::string& file_path) {
    return createTexture(TERRAIN_RESOURCES_SUBPATH, file_path);
}

void TerrainController::renderEagleEye() {
    // Dest Area is after the terrain area
    Area destArea(screen_configuration.getWidth() + EAGLE_EYE_X_OFFSET, EAGLE_EYE_Y_OFFSET, EAGLE_EYE_WIDTH, EAGLE_EYE_HEIGHT);

    Area terrainSrcArea(0, 0, this->terrain_width, this->terrain_height);
    this->terrain_texture->render(terrainSrcArea, destArea);

    Area eagleEyeSrcArea(0, 0, EAGLE_EYE_SQUARE_ORIGIN_WIDTH, EAGLE_EYE_SQUARE_ORIGIN_HEIGHT);
    // How much of the terrain is being displayed in the screen
    double view_width_rate = (static_cast<double>(destArea.getWidth()) / static_cast<double>(this->terrain_width));
    double view_height_rate = (static_cast<double>(destArea.getHeight()) / static_cast<double>(this->terrain_height));

    // Resized the offset for the eagle_eye map
    double x_offset = static_cast<double>(screen_information.getOffsetX()) * view_width_rate;
    double y_offset = static_cast<double>(screen_information.getOffsetY()) * view_height_rate;

    // Calculate the coordinates from the square
    double x_coordinate = static_cast<double>(destArea.getX()) - x_offset;
    double y_coordinate = static_cast<double>(destArea.getY()) - y_offset;

    // Recalculate the size
    double width = static_cast<double>(screen_configuration.getWidth()) * view_width_rate;
    double height = static_cast<double>(screen_configuration.getHeight()) * view_height_rate;

    Area eagleDestArea(
            static_cast<int>(x_coordinate),
            static_cast<int>(y_coordinate),
            static_cast<int>(width),
            static_cast<int>(height));
    client_sprites_supplier[EAGLE_EYE_SQUARE]->render(eagleEyeSrcArea, eagleDestArea);
}

void TerrainController::update(const GameStatusEvent &event) {
    // Append both picturables and selectables
    std::vector<Picturable> picturables(event.picturables);
    picturables.insert(
            std::end(picturables),
            std::begin(event.selectedObjects),
            std::end(event.selectedObjects));

    if (!picturables.empty()) {
        this->pending_changes = true;
    }

    // Update/create/delete the picturables
    std::for_each(picturables.begin(), picturables.end(), [this](Picturable &picturable) {
        // Localize texture to be rendered
        SdlTexture* texture = picturables_map[picturable.name][picturable.sprite_direction][picturable.sprite_motion][picturable.player_id];
        if (texture == nullptr) {
            std::cout << "Texture could not been found!" << std::endl;
        } else {

            auto picturable_it = std::find_if(this->picturables.begin(), this->picturables.end(),
                                              [&](ClientPicturable *sdlPicturable) {
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
                // Create a new ClientPicturable
                this->picturables.push_back(new ClientPicturable(picturable, texture, this->client_sprites_supplier));
            }
        }
    });
}

void TerrainController::render() {
    Area srcArea(0 - screen_information.getOffsetX(), 0 - screen_information.getOffsetY(), screen_configuration.getWidth(), screen_configuration.getHeight());
    Area destArea(0, screen_configuration.getHeightOffset(), screen_configuration.getWidth(), screen_configuration.getHeight());

    terrain_texture->render(srcArea, destArea);

    // Render picturables with priority first
    std::for_each(picturables.begin(), picturables.end(), [&](ClientPicturable *sdlPicturable) {
        if (sdlPicturable->hasPriority()) {
            sdlPicturable->render(screen_information.getOffsetX(), screen_information.getOffsetY(), screen_configuration.getWidth(), screen_configuration.getHeightOffset());
        }
    });

    // Render the SdlPicturables
    std::for_each(picturables.begin(), picturables.end(), [&](ClientPicturable *sdlPicturable) {
        if (!sdlPicturable->hasPriority()) {
            sdlPicturable->render(screen_information.getOffsetX(), screen_information.getOffsetY(), screen_configuration.getWidth(), screen_configuration.getHeightOffset());
        }
    });

    // Render the eagle eye
    renderEagleEye();

    window->render();
    pending_changes = false;
}

void TerrainController::move(enum Movement movement) {
    int current_x_offset = screen_information.getOffsetX();
    int current_y_offset = screen_information.getOffsetY();

    switch (movement) {
        case UP: {
            if (current_y_offset < 0) {
                screen_information.setOffsetY(current_y_offset + TILE_PIXEL_RATE);
                this->pending_changes = true;
            }
            break;
        }
        case DOWN: {
            if ((current_y_offset + this->terrain_height - screen_configuration.getHeight()) > 0) {
                screen_information.setOffsetY(current_y_offset - TILE_PIXEL_RATE);
                this->pending_changes = true;
            }
            break;
        }
        case LEFT: {
            if (current_x_offset < 0) {
                screen_information.setOffsetX(current_x_offset + TILE_PIXEL_RATE);
                this->pending_changes = true;
            }
            break;
        }
        case RIGHT: {
            if ((current_x_offset + this->terrain_width - screen_configuration.getWidth()) > 0) {
                screen_information.setOffsetX(current_x_offset - TILE_PIXEL_RATE);
                this->pending_changes = true;
            }
            break;
        }
        default: {
            break;
        }

    }
}

bool TerrainController::resolvePendingAction(const SDL_MouseButtonEvent &mouse_event, EventsLooperThread *processer, const std::function<void(EventsLooperThread *, int, int, Point, Point)>& push_function) {
    return false;
}
void TerrainController::parseMouseClick(const SDL_MouseButtonEvent& mouse_event, EventsLooperThread* processer, const std::function<void(EventsLooperThread*, int, int, Point, Point)>& push_function) {
    if (includes(mouse_event.x, mouse_event.y)) {
        temporary_position = screen_information.getRelativePoint(mouse_event.y, mouse_event.x);
        clicked = true;
    } else {
        clicked = false;
    }
}
void TerrainController::parseMouseRelease(const SDL_MouseButtonEvent &mouse_event, EventsLooperThread *processer, const std::function<void(EventsLooperThread *, int, int, Point, Point)>& push_function) {
    if (clicked) {
        switch (mouse_event.button) {
            case SDL_BUTTON_LEFT: {
                push_function(processer, LEFT_CLICK_EVENT_TYPE, 0, temporary_position,
                              screen_information.getRelativePoint(mouse_event.y, mouse_event.x));
                break;
            }
            case SDL_BUTTON_RIGHT: {
                push_function(processer, RIGHT_CLICK_EVENT_TYPE, 0, temporary_position,
                              screen_information.getRelativePoint(mouse_event.y, mouse_event.x));
                break;
            }
            default:
                break;
        }
    }
    clicked = false;
}

TerrainController::~TerrainController() {
    // Delete all the terrain textures
    for (auto& terrain_texture : this->terrains_textures_map) {
        delete terrain_texture.second;
    }

    // Delete the terrain texture
    if (!this->terrain_texture) {
        delete this->terrain_texture;
    }

    // Delete all the picturable textures
    for (auto& unit_textures : this->picturables_map) {
        // Iterate directions
        for (auto& unit_direction : unit_textures.second) {
            // Iterate motions
            for (auto& unit_motion : unit_direction.second) {
                // Iterate colors
                for (auto& unit_color : unit_motion.second) {
                    // Iterate colors
                    delete unit_color.second;
                }
            }
        }
    }

    // Delete all the picturables
    for (auto& picturable : this->picturables) {
        delete picturable;
    }
}
