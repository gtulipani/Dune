#include "ButtonsController.h"

// STL Libraries
#include <algorithm>

// Commons Libraries
#include <events/ClientEvent.h>

// SDL Libraries
#include <SDL_events.h>

#define MAIN_BUTTONS_Y_OFFSET 260
#define MAIN_BUTTON_WIDTH 40
#define MAIN_BUTTON_HEIGHT 40

#define MAIN_BUTTONS_BUILDING_ICONS_DIVISION 10

#define BUILDING_ICON_Y_OFFSET (MAIN_BUTTONS_Y_OFFSET + MAIN_BUTTON_HEIGHT + MAIN_BUTTONS_BUILDING_ICONS_DIVISION)
#define BUILDING_ICON_X_OFFSET 10
#define BUILDING_ICON_WIDTH 90
#define BUILDING_ICON_HEIGHT 70

#define BUILDING_ICONS_QUANTITY 4

#define BUTTONS_RESOURCES_PATH std::string("resources/images/game/panel/")

typedef enum PannelButtons {
    REPAIR_BUTTON_ICON = 0,
    SELL_BUTTON_ICON = 1,
    STATUS_BUTTON_ICON = 2,
    GUARD_BUTTON_ICON = 3,
    RETREAT_BUTTON_ICON = 4,
    CONSTRUCTION_CENTER_ICON = 5,
    WIND_TRAPS_ICON = 6,
    REFINERY_ICON = 7,
    ATREIDES_BARRACKS_ICON = 8,
    HARKONNEN_BARRACKS_ICON = 9,
    ORDOS_BARRACKS_ICON = 10,
    LIGHT_FACTORY_ICON = 11,
    HEAVY_FACTORY_ICON = 12,
    SILO_ICON = 13,
    PALACE_ICON = 14,
    LIGHT_INFANTRY_ICON = 15,
    HEAVY_INFANTRY_ICON = 16,
    TRIKE_ICON = 17,
    RAIDER_ICON = 18,
    ATREIDES_TANK_ICON = 19,
    HARKONNEN_TANK_ICON = 20,
    ORDOS_TANK_ICON = 21,
    HARVESTER_ICON = 22
} PannelButtons;

ButtonsController::ButtonsController(SdlWindow *window) :
        window(window) {}

Point ButtonsController::getGlobalPosition(Point point) {
    return { point.row, point.col + this->screen_width_offset };
}

Point ButtonsController::getRelativePosition(Point point) {
    return { point.row, point.col - this->screen_width_offset };
}

Point ButtonsController::buildMainButtonRelativePosition(int order) {
    return { MAIN_BUTTONS_Y_OFFSET, order * MAIN_BUTTON_WIDTH };
}

Point ButtonsController::buildOptionalButtonRelativePosition(int order) {
    return { BUILDING_ICON_Y_OFFSET + (order * BUILDING_ICON_HEIGHT), BUILDING_ICON_X_OFFSET };
}

SdlTexture *ButtonsController::createButtonTexture(std::string file_path) {
    return new SdlTexture(BUTTONS_RESOURCES_PATH + file_path, this->window);
}

void ButtonsController::buildButtons() {
    // Store main buttons icons textures
    buttons_textures_map.emplace(REPAIR_BUTTON_ICON, createButtonTexture("repair_button.png"));
    buttons_textures_map.emplace(SELL_BUTTON_ICON, createButtonTexture("sell_button.png"));
    buttons_textures_map.emplace(STATUS_BUTTON_ICON, createButtonTexture("status_button.png"));
    buttons_textures_map.emplace(GUARD_BUTTON_ICON, createButtonTexture("guard_button.png"));
    buttons_textures_map.emplace(RETREAT_BUTTON_ICON, createButtonTexture("retreat_button.png"));

    // Store buildings icons textures
    //buttons_textures_map.emplace(CONSTRUCTION_CENTER_ICON, createButtonTexture("construction_center_icon.png"));
    buttons_textures_map.emplace(WIND_TRAPS_ICON, createButtonTexture("wind_trap_icon.png"));
    buttons_textures_map.emplace(REFINERY_ICON, createButtonTexture("refinery_icon.png"));
    buttons_textures_map.emplace(ATREIDES_BARRACKS_ICON, createButtonTexture("atreides_barracks_icon.png"));
    buttons_textures_map.emplace(HARKONNEN_BARRACKS_ICON, createButtonTexture("harkonnen_barracks_icon.png"));
    buttons_textures_map.emplace(ORDOS_BARRACKS_ICON, createButtonTexture("ordos_barracks_icon.png"));
    buttons_textures_map.emplace(LIGHT_FACTORY_ICON, createButtonTexture("light_factory_icon.png"));
    buttons_textures_map.emplace(HEAVY_FACTORY_ICON, createButtonTexture("heavy_factory_icon.png"));
    buttons_textures_map.emplace(SILO_ICON, createButtonTexture("silo_icon.png"));
    buttons_textures_map.emplace(PALACE_ICON, createButtonTexture("palace_icon.png"));

    // Store units icons textures
    buttons_textures_map.emplace(LIGHT_INFANTRY_ICON, createButtonTexture("light_infantry_icon.png"));
    buttons_textures_map.emplace(HEAVY_INFANTRY_ICON, createButtonTexture("heavy_infantry_icon.png"));
    buttons_textures_map.emplace(TRIKE_ICON, createButtonTexture("trike_icon.png"));
    buttons_textures_map.emplace(RAIDER_ICON, createButtonTexture("raider_icon.png"));
    buttons_textures_map.emplace(ATREIDES_TANK_ICON, createButtonTexture("atreides_tank_icon.png"));
    buttons_textures_map.emplace(HARKONNEN_TANK_ICON, createButtonTexture("harkonnen_tank_icon.png"));
    buttons_textures_map.emplace(ORDOS_TANK_ICON, createButtonTexture("ordos_tank_icon.png"));
    buttons_textures_map.emplace(HARVESTER_ICON, createButtonTexture("harvester_icon.png"));
}

void ButtonsController::loadMainButtons() {
    // The main buttons will be rendered only once directly in the texture
    // Load main buttons textures
    mandatory_buttons.emplace_back(MAIN_BUTTON_WIDTH, MAIN_BUTTON_HEIGHT, buildMainButtonRelativePosition(0), "", buttons_textures_map[REPAIR_BUTTON_ICON]);
    mandatory_buttons.emplace_back(MAIN_BUTTON_WIDTH, MAIN_BUTTON_HEIGHT, buildMainButtonRelativePosition(1), "", buttons_textures_map[SELL_BUTTON_ICON]);
    mandatory_buttons.emplace_back(MAIN_BUTTON_WIDTH, MAIN_BUTTON_HEIGHT, buildMainButtonRelativePosition(2), "", buttons_textures_map[STATUS_BUTTON_ICON]);
    mandatory_buttons.emplace_back(MAIN_BUTTON_WIDTH, MAIN_BUTTON_HEIGHT, buildMainButtonRelativePosition(3), "", buttons_textures_map[GUARD_BUTTON_ICON]);
    mandatory_buttons.emplace_back(MAIN_BUTTON_WIDTH, MAIN_BUTTON_HEIGHT, buildMainButtonRelativePosition(4), "", buttons_textures_map[RETREAT_BUTTON_ICON]);
}

void ButtonsController::loadButtonsPanel() {
    // The optional buttons will be rendered directly in the window
    // Initial light_factory and wind_trap buildings
    available_buttons.emplace_back(BUILDING_ICON_WIDTH, BUILDING_ICON_HEIGHT, getGlobalPosition(buildOptionalButtonRelativePosition(0)), CREATE_BUILDING_LIGHT_FACTORY, buttons_textures_map[LIGHT_FACTORY_ICON]);
    available_buttons.emplace_back(BUILDING_ICON_WIDTH, BUILDING_ICON_HEIGHT, getGlobalPosition(buildOptionalButtonRelativePosition(1)), CREATE_BUILDING_WIND_TRAPS, buttons_textures_map[WIND_TRAPS_ICON]);
}

void ButtonsController::renderPanelTexture() {
    // Now we render the main texture with only the background images and the main buttons
    // Load background image
    Area srcArea(0, 0, this->screen_width, this->screen_height);
    Area destArea(0, 0, this->screen_width, this->screen_height);
    SdlTexture(BUTTONS_RESOURCES_PATH + "/background.png", this->window).render(srcArea, destArea);

    // Load background image for optional buttons
    srcArea = Area(0, 0, BUILDING_ICON_WIDTH * 2, BUILDING_ICON_HEIGHT * BUILDING_ICONS_QUANTITY);
    destArea = Area(BUILDING_ICON_X_OFFSET, BUILDING_ICON_Y_OFFSET, BUILDING_ICON_WIDTH * 2, BUILDING_ICON_HEIGHT * BUILDING_ICONS_QUANTITY);
    SdlTexture(BUTTONS_RESOURCES_PATH + "/optional_buttons_background.png", this->window).render(srcArea, destArea);

    // Load mandatory buttons
    std::for_each(mandatory_buttons.begin(), mandatory_buttons.end(), [&](PanelButton &button) {
        button.render(0, 0);
    });
}

void ButtonsController::fill() {
    this->window->fill();
}

void ButtonsController::configure(int screen_width, int screen_height, int screen_width_offset) {
    this->screen_width = screen_width;
    this->screen_height = screen_height;

    this->screen_width_offset = screen_width_offset;

    buildButtons();

    this->panel_texture = new SdlTexture(screen_width, screen_height, this->window->getRenderer());
    this->panel_texture->setAsTarget();

    loadMainButtons();
    loadButtonsPanel();
    renderPanelTexture();

    this->window->render();
    this->window->setAsTarget();
}

void ButtonsController::render() {
    // Render the main texture containing the background image and the main buttons
    Area srcArea(0, 0, this->screen_width, this->screen_height);
    Area destArea(screen_width_offset, 0, this->screen_width, this->screen_height);
    this->panel_texture->render(srcArea, destArea);

    // Render each one of the available buttons
    std::for_each(available_buttons.begin(), available_buttons.end(), [&](PanelButton &button) {
        button.render(0, 0);
    });

    this->window->render();
}

void ButtonsController::parseClick(SDL_MouseButtonEvent& mouse_event,
                                   EventsLooperThread* processer,
                                   std::function<void(EventsLooperThread*, std::string, Point)> push_function) {
    Point position(mouse_event.y, mouse_event.x);
    switch (mouse_event.button) {
        case SDL_BUTTON_LEFT: {
            bool found = false;
            // Most likely a click on a building icon
            for (const PanelButton& button : optional_buttons) {
                if (button.includesPosition(position) && button.includesExternalAction()) {
                    push_function(processer, button.getAction(), position);
                    found = true;
                }
            }
            if (!found) {
                for (const PanelButton& button : mandatory_buttons) {
                    if (button.includesPosition(getRelativePosition(position))) {
                        //push_function(processer, button.getAction(), position);
                    }
                }
            }
            break;
        }
        case SDL_BUTTON_RIGHT: {
            break;
        }
        default:
            break;
    }
}