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

ButtonsController::ButtonsController(SdlWindow *window, ClientSpritesSupplier &client_sprites_supplier) :
        window(window),
        client_sprites_supplier(client_sprites_supplier) {}

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

void ButtonsController::loadMainButtons() {
    // The main buttons will be rendered only once directly in the texture
    // Load main buttons textures
    mandatory_buttons.emplace_back(MAIN_BUTTON_WIDTH, MAIN_BUTTON_HEIGHT, buildMainButtonRelativePosition(0), "", client_sprites_supplier[REPAIR_BUTTON_ICON]);
    mandatory_buttons.emplace_back(MAIN_BUTTON_WIDTH, MAIN_BUTTON_HEIGHT, buildMainButtonRelativePosition(1), "", client_sprites_supplier[SELL_BUTTON_ICON]);
    mandatory_buttons.emplace_back(MAIN_BUTTON_WIDTH, MAIN_BUTTON_HEIGHT, buildMainButtonRelativePosition(2), "", client_sprites_supplier[STATUS_BUTTON_ICON]);
    mandatory_buttons.emplace_back(MAIN_BUTTON_WIDTH, MAIN_BUTTON_HEIGHT, buildMainButtonRelativePosition(3), "", client_sprites_supplier[GUARD_BUTTON_ICON]);
    mandatory_buttons.emplace_back(MAIN_BUTTON_WIDTH, MAIN_BUTTON_HEIGHT, buildMainButtonRelativePosition(4), "", client_sprites_supplier[RETREAT_BUTTON_ICON]);
}

void ButtonsController::loadButtonsPanel() {
    // Initial light_factory and wind_trap buildings
    available_buttons.emplace_back(BUILDING_ICON_WIDTH, BUILDING_ICON_HEIGHT, getGlobalPosition(buildOptionalButtonRelativePosition(0)), CREATE_BUILDING_LIGHT_FACTORY, client_sprites_supplier[LIGHT_FACTORY_ICON]);
    available_buttons.emplace_back(BUILDING_ICON_WIDTH, BUILDING_ICON_HEIGHT, getGlobalPosition(buildOptionalButtonRelativePosition(1)), CREATE_BUILDING_WIND_TRAPS, client_sprites_supplier[WIND_TRAPS_ICON]);
}

void ButtonsController::renderPanelTexture() {
    // Now we render the main texture with only the background images and the main buttons
    // Load background image
    Area srcArea(0, 0, this->screen_width, this->screen_height);
    Area destArea(0, 0, this->screen_width, this->screen_height);
    client_sprites_supplier[BACKGROUND]->render(srcArea, destArea);

    // Load background image for optional buttons
    srcArea = Area(0, 0, BUILDING_ICON_WIDTH * 2, BUILDING_ICON_HEIGHT * BUILDING_ICONS_QUANTITY);
    destArea = Area(BUILDING_ICON_X_OFFSET, BUILDING_ICON_Y_OFFSET, BUILDING_ICON_WIDTH * 2, BUILDING_ICON_HEIGHT * BUILDING_ICONS_QUANTITY);
    client_sprites_supplier[BUTTONS_BACKGROUND]->render(srcArea, destArea);

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
            for (const PanelButton& button : available_buttons) {
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