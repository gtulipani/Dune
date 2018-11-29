#include <utility>

#include "ButtonsController.h"

// STL Libraries
#include <algorithm>

// Commons Libraries
#include <events/ClientEvent.h>

// SDL Libraries
#include <SDL_events.h>
#include <Sprites.h>

// Client Libraries
#include "UnitButton.h"
#include "BuildingButton.h"
#include "RequiresTerrainControllerActionException.h"

#define EAGLE_EYE_Y_OFFSET 20
#define EAGLE_EYE_X_OFFSET 10
#define EAGLE_EYE_WIDTH 180
#define EAGLE_EYE_HEIGHT 220

#define BUILDING_ICON_Y_OFFSET (EAGLE_EYE_Y_OFFSET + EAGLE_EYE_HEIGHT + EAGLE_EYE_Y_OFFSET)
#define BUILDING_ICON_X_OFFSET 10
#define BUILDING_ICON_WIDTH 90
#define BUILDING_ICON_HEIGHT 70

#define BUILDING_ICONS_QUANTITY 4

ButtonsController::ButtonsController(SdlWindow *window, ClientSpritesSupplier &client_sprites_supplier, TerrainController* terrain_controller, std::function<void(TerrainController*, Area)> map_renderer) :
        window(window),
        client_sprites_supplier(client_sprites_supplier),
        terrain_controller(terrain_controller),
        map_renderer(std::move(map_renderer)) {}

Point ButtonsController::getGlobalPosition(Point point) {
    return {point.row, point.col + this->screen_width_offset};
}

Point ButtonsController::getRelativePosition(Point point) {
    return {point.row, point.col - this->screen_width_offset};
}

Point ButtonsController::buildOptionalButtonRelativePosition(int order) {
    return {BUILDING_ICON_Y_OFFSET + (order * BUILDING_ICON_HEIGHT), BUILDING_ICON_X_OFFSET};
}

void ButtonsController::loadButtonsPanel() {
    // Initial light_factory and wind_trap buildings
    available_buttons.push_back(new BuildingButton(BUILDING_ICON_WIDTH, BUILDING_ICON_HEIGHT,
                                                     getGlobalPosition(buildOptionalButtonRelativePosition(0)),
                                                     LIGHT_FACTORY,
                                                     LIGHT_FACTORY_ICON,
                                                     {CREATE_LIGHT_FACTORY_TYPE, LOCATE_BUILDING_TYPE},
                                                     client_sprites_supplier));
    available_buttons.push_back(new BuildingButton(BUILDING_ICON_WIDTH, BUILDING_ICON_HEIGHT,
                                                     getGlobalPosition(buildOptionalButtonRelativePosition(1)),
                                                     WIND_TRAPS,
                                                     WIND_TRAPS_ICON,
                                                     {CREATE_WIND_TRAPS_TYPE, LOCATE_BUILDING_TYPE},
                                                     client_sprites_supplier));
}

void ButtonsController::renderPanelTexture() {
    // Now we render the main texture with only the background images and the main buttons
    // Load background image
    Area srcArea(0, 0, this->screen_width, this->screen_height);
    Area destArea(0, 0, this->screen_width, this->screen_height);
    client_sprites_supplier[BACKGROUND]->render(srcArea, destArea);

    // Load background image for optional buttons
    srcArea = Area(0, 0, BUILDING_ICON_WIDTH * 2, BUILDING_ICON_HEIGHT * BUILDING_ICONS_QUANTITY);
    destArea = Area(BUILDING_ICON_X_OFFSET, BUILDING_ICON_Y_OFFSET, BUILDING_ICON_WIDTH * 2,
                    BUILDING_ICON_HEIGHT * BUILDING_ICONS_QUANTITY);
    client_sprites_supplier[BUTTONS_BACKGROUND]->render(srcArea, destArea);
}

void ButtonsController::renderEagleEye() {
    Area destArea(screen_width_offset + EAGLE_EYE_X_OFFSET, EAGLE_EYE_Y_OFFSET, EAGLE_EYE_WIDTH, EAGLE_EYE_HEIGHT);
    map_renderer(terrain_controller, destArea);
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

    loadButtonsPanel();
    renderPanelTexture();

    this->window->render();
    this->window->setAsTarget();
}

void ButtonsController::render() {
    // Render the main texture containing the background image and the main buttons
    Area srcArea(0, 0, screen_width, screen_height);
    Area destArea(screen_width_offset, 0, screen_width, screen_height);
    panel_texture->render(srcArea, destArea);

    // Render the eagle eye map
    renderEagleEye();

    // Render each one of the available buttons
    std::for_each(available_buttons.begin(), available_buttons.end(), [&](PanelButton *button) {
        button->render(0, 0);
    });

    window->render();
    pending_changes = false;
}

void ButtonsController::refresh() {
    if (pending_changes) {
        render();
    }
}

void ButtonsController::processPicturables(std::vector<Picturable>& picturables) {
    // We sort the picturables leaving the once with less porcentage at the beginning
    std::sort(picturables.begin(), picturables.end(), [](const Picturable &p1, const Picturable &p2) -> bool {
        return (p1.porcentage < p2.porcentage);
    });

    // We iterate through the buttons and search for the first appearence for the type, which will be the one with less percentage
    std::for_each(available_buttons.begin(), available_buttons.end(), [this, picturables](PanelButton *button) {
        auto it = std::find_if(picturables.begin(), picturables.end(), [button](const Picturable &picturable) {
            return button->hasType(picturable.type);
        });
        if (it != picturables.end()) {
            if (button->update(it->id, it->porcentage)) {
                pending_changes = true;
            }

        }
    });
}

bool ButtonsController::resolvePendingAction(SDL_MouseButtonEvent &mouse_event, EventsLooperThread *processer,
                    std::function<void(EventsLooperThread *, int, int, Point,
                                       Point)> push_function) {
    Point position(mouse_event.y, mouse_event.x); // Review this, it's not taking offset into account
    switch (mouse_event.button) {
        case SDL_BUTTON_LEFT: {
            bool resolved = false;
            for (PanelButton *button : available_buttons) {
                if (button->isWaitingForAction()) {
                    // Pass the new event info to the button and mark it as resolved
                    button->resolve(position, processer, push_function);
                    if (button->hasChanged()) {
                        this->pending_changes = true;
                    }
                    resolved = true;
                }
            }
            return resolved;
        }
        case SDL_BUTTON_RIGHT: {
            return false;
        }
        default:
            return false;
    }
}

void ButtonsController::parseMouseClickButton(SDL_MouseButtonEvent &mouse_event, EventsLooperThread *processer,
                                              std::function<void(EventsLooperThread *, int, int, Point,
                                                                 Point)> push_function) {}

void ButtonsController::parseMouseReleaseButton(SDL_MouseButtonEvent &mouse_event,
                                                EventsLooperThread *processer,
                                                std::function<void(EventsLooperThread *, int, int, Point,
                                                                   Point)> push_function) {
    Point position(mouse_event.y, mouse_event.x);
    switch (mouse_event.button) {
        case SDL_BUTTON_LEFT: {
            // Most likely a click on a building icon
            for (PanelButton *button : available_buttons) {
                if (button->includesPosition(position) && button->includesExternalAction()) {
                    // We are sending an action, so we are not going to use the positions for now
                    button->click(processer, push_function);
                    if (button->hasChanged()) {
                        this->pending_changes = true;
                    }
                }
            }
        }
        case SDL_BUTTON_RIGHT: {
            break;
        }
        default:
            break;
    }
}

void ButtonsController::move() {
    renderEagleEye();
}

ButtonsController::~ButtonsController() {
    if (!this->panel_texture) {
        delete this->panel_texture;
    }

    for (auto &button : this->available_buttons) {
        delete button;
    }
}
