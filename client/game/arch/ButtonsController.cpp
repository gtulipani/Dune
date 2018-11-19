#include <algorithm>
#include "ButtonsController.h"

#define BUTTON_WIDTH 80
#define BUTTON_HEIGHT 80
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

void ButtonsController::configure(int width, int height, int width_offset, int height_offset) {
    this->width = width;
    this->height = height;
    this->width_offset = width_offset;
    this->height_offset = height_offset;

    buildButtons();

    /*this->panel_texture = SdlTexture(width, height, this->window->getRenderer());
    this->panel_texture.setAsTarget();

    loadButtonsPanel();

    this->window->render();
    this->window->setAsTarget();*/
}

void ButtonsController::render() {
    // Render the buttons
    std::for_each(buttons.begin(), buttons.end(), [&](PanelButton &button) {
        button.render(0, 0);
    });
    this->window->render();

    /*Area srcArea(0, 0, this->width, this->height);
    Area destArea(0, 0, this->width, this->height);
    this->panel_texture.render(srcArea, destArea);*/
}

void ButtonsController::loadButtonsPanel() {
    // Render the buttons
    std::for_each(buttons.begin(), buttons.end(), [&](PanelButton &button) {
        button.render(0, 50);
    });
}