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


void ButtonsController::buildButtons() {
    // The mandatory buttons will be rendered only once directly in the texture
    // Store main buttons textures
    mandatory_buttons.emplace_back(MAIN_BUTTON_WIDTH, MAIN_BUTTON_HEIGHT, buildMainButtonRelativePosition(REPAIR_BUTTON), "", BUTTONS_RESOURCES_PATH + "/repair_button.png", window);
    mandatory_buttons.emplace_back(MAIN_BUTTON_WIDTH, MAIN_BUTTON_HEIGHT, buildMainButtonRelativePosition(SELL_BUTTON), "", BUTTONS_RESOURCES_PATH + "/sell_button.png", window);
    mandatory_buttons.emplace_back(MAIN_BUTTON_WIDTH, MAIN_BUTTON_HEIGHT, buildMainButtonRelativePosition(STATUS_BUTTON), "", BUTTONS_RESOURCES_PATH + "/status_button.png", window);
    mandatory_buttons.emplace_back(MAIN_BUTTON_WIDTH, MAIN_BUTTON_HEIGHT, buildMainButtonRelativePosition(GUARD_BUTTON), "", BUTTONS_RESOURCES_PATH + "/guard_button.png", window);
    mandatory_buttons.emplace_back(MAIN_BUTTON_WIDTH, MAIN_BUTTON_HEIGHT, buildMainButtonRelativePosition(RETREAT_BUTTON), "", BUTTONS_RESOURCES_PATH + "/retreat_button.png", window);

    // The optional buttons will be rendered directly in the window
    // Initial light_factory and wind_trap buildings
    optional_buttons.emplace_back(BUILDING_ICON_WIDTH, BUILDING_ICON_HEIGHT, getGlobalPosition(buildOptionalButtonRelativePosition(0)), CREATE_BUILDING_TYPE, BUTTONS_RESOURCES_PATH + "/light_factory_icon.png", window);
    optional_buttons.emplace_back(BUILDING_ICON_WIDTH, BUILDING_ICON_HEIGHT, getGlobalPosition(buildOptionalButtonRelativePosition(1)), CREATE_BUILDING_TYPE, BUTTONS_RESOURCES_PATH + "/wind_trap_icon.png", window);
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

    std::for_each(optional_buttons.begin(), optional_buttons.end(), [&](PanelButton &button) {
        button.render(0, 0);
    });

    this->window->render();
}

void ButtonsController::loadButtonsPanel() {
    // Load background image
    Area srcArea(0, 0, this->screen_width, this->screen_height);
    Area destArea(0, 0, this->screen_width, this->screen_height);
    SdlTexture(BUTTONS_RESOURCES_PATH + "/background.png", this->window).render(srcArea, destArea);

    // Load background image for optional buttons
    srcArea = Area(0, 0, BUILDING_ICON_WIDTH * 2, BUILDING_ICON_HEIGHT * BUILDING_ICONS_QUANTITY);
    destArea = Area(BUILDING_ICON_X_OFFSET, BUILDING_ICON_Y_OFFSET, BUILDING_ICON_WIDTH * 2, BUILDING_ICON_HEIGHT * BUILDING_ICONS_QUANTITY);
    SdlTexture(BUTTONS_RESOURCES_PATH + "/optional_buttons_background.png", this->window).render(srcArea, destArea);

    // Render the buttons
    std::for_each(mandatory_buttons.begin(), mandatory_buttons.end(), [&](PanelButton &button) {
        button.render(0, 0);
    });
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