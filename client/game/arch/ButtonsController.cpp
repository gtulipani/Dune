#include <algorithm>
#include "ButtonsController.h"

#define MAIN_BUTTONS_Y_OFFSET 200
#define MAIN_BUTTON_WIDTH 40
#define MAIN_BUTTON_HEIGHT 40

#define BUILDING_ICON_Y_OFFSET (MAIN_BUTTONS_Y_OFFSET + MAIN_BUTTON_HEIGHT)
#define BUILDING_ICON_X_OFFSET 10
#define BUILDING_ICON_WIDTH 90
#define BUILDING_ICON_HEIGHT 90

#define BUTTONS_RESOURCES_PATH std::string("resources/images/game/panel")

typedef enum PannelButton {
    REPAIR_BUTTON = 0,
    SELL_BUTTON = 1,
    STATUS_BUTTON = 2,
    GUARD_BUTTON = 3,
    RETREAT_BUTTON = 4
} PannelButton;

ButtonsController::ButtonsController(SdlWindow *window) :
        window(window) {}

Point ButtonsController::buildGlobalPosition(int order) {
    return { this->screen_width_offset + (order * MAIN_BUTTON_WIDTH), MAIN_BUTTONS_Y_OFFSET };
}

Point ButtonsController::buildMainButtonRelativePosition(int order) {
    return { MAIN_BUTTONS_Y_OFFSET, order * MAIN_BUTTON_WIDTH };
}

Point ButtonsController::buildBuildingButtonRelativePosition(int order) {
    return { BUILDING_ICON_Y_OFFSET + (order * BUILDING_ICON_HEIGHT), 0 };
}

void ButtonsController::buildButtons() {
    // Store main buttons textures
    buttons.emplace_back(MAIN_BUTTON_WIDTH, MAIN_BUTTON_HEIGHT, buildMainButtonRelativePosition(REPAIR_BUTTON) , BUTTONS_RESOURCES_PATH + "/repair_button.png", window);
    buttons.emplace_back(MAIN_BUTTON_WIDTH, MAIN_BUTTON_HEIGHT, buildMainButtonRelativePosition(SELL_BUTTON), BUTTONS_RESOURCES_PATH + "/sell_button.png", window);
    buttons.emplace_back(MAIN_BUTTON_WIDTH, MAIN_BUTTON_HEIGHT, buildMainButtonRelativePosition(STATUS_BUTTON), BUTTONS_RESOURCES_PATH + "/status_button.png", window);
    buttons.emplace_back(MAIN_BUTTON_WIDTH, MAIN_BUTTON_HEIGHT, buildMainButtonRelativePosition(GUARD_BUTTON), BUTTONS_RESOURCES_PATH + "/guard_button.png", window);
    buttons.emplace_back(MAIN_BUTTON_WIDTH, MAIN_BUTTON_HEIGHT, buildMainButtonRelativePosition(RETREAT_BUTTON), BUTTONS_RESOURCES_PATH + "/retreat_button.png", window);

    // Initial light_factory and wind_trap buildings
    buttons.emplace_back(BUILDING_ICON_WIDTH, BUILDING_ICON_HEIGHT, buildBuildingButtonRelativePosition(0), BUTTONS_RESOURCES_PATH + "/light_factory_icon.png", window);
    buttons.emplace_back(BUILDING_ICON_WIDTH, BUILDING_ICON_HEIGHT, buildBuildingButtonRelativePosition(1), BUTTONS_RESOURCES_PATH + "/wind_trap_icon.png", window);
}

void ButtonsController::fill() {
    this->window->fill();
}

void ButtonsController::configure(int screen_width, int screen_height, int screen_width_offset) {
    this->screen_width = screen_width;
    this->screen_height = screen_height;

    this->screen_width_offset = screen_width_offset;

    buildButtons();

    this->panel_texture = SdlTexture(screen_width, screen_height, this->window->getRenderer());
    this->panel_texture.setAsTarget();

    loadButtonsPanel();

    this->window->render();
    this->window->setAsTarget();
}

void ButtonsController::render() {
    // Render the buttons
    Area srcArea(0, 0, this->screen_width, this->screen_height);
    Area destArea(screen_width_offset, 0, this->screen_width, this->screen_height);
    this->panel_texture.render(srcArea, destArea);

    this->window->render();
}

void ButtonsController::loadButtonsPanel() {
    // Render the buttons
    std::for_each(buttons.begin(), buttons.end(), [&](PanelButton &button) {
        button.render(0, 0);
    });
}