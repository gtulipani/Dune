#include <algorithm>
#include "ButtonsController.h"

#define BUTTON_WIDTH 40
#define BUTTON_HEIGHT 40

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

void ButtonsController::buildButtons() {
    // Store units textures
    buttons.emplace_back(REPAIR_BUTTON, BUTTON_WIDTH, BUTTON_HEIGHT, BUTTONS_RESOURCES_PATH + "/repair_button.png", window);
    buttons.emplace_back(SELL_BUTTON, BUTTON_WIDTH, BUTTON_HEIGHT, SdlTexture(BUTTONS_RESOURCES_PATH + "/sell_button.png", window));
    buttons.emplace_back(STATUS_BUTTON, BUTTON_WIDTH, BUTTON_HEIGHT, SdlTexture(BUTTONS_RESOURCES_PATH + "/status_button.png", window));
    buttons.emplace_back(GUARD_BUTTON, BUTTON_WIDTH, BUTTON_HEIGHT, SdlTexture(BUTTONS_RESOURCES_PATH + "/guard_button.png", window));
    buttons.emplace_back(RETREAT_BUTTON, BUTTON_WIDTH, BUTTON_HEIGHT, SdlTexture(BUTTONS_RESOURCES_PATH + "/retreat_button.png", window));
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
        button.render(0, 200);
    });
}