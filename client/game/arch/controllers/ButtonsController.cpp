#include <utility>

#include "ButtonsController.h"

// STL Libraries
#include <algorithm>

// Commons Libraries
#include <events/ClientEvent.h>
#include <UnitsAndBuildings.h>

// SDL Libraries
#include <SDL_events.h>
#include <Sprites.h>

// Client Libraries
#include "../buttons/UnitButton.h"
#include "../buttons/BuildingButton.h"
#include "../buttons/ButtonsFactory.h"
#include "RequiresTerrainControllerActionException.h"
#include "ScreenController.h"

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

Point ButtonsController::buildOptionalButtonRelativePosition(int row_order, int col_order) {
    // Order starts from zero
    return {PANEL_BUTTON_ICON_Y_OFFSET + ((row_order - 1) * PANEL_BUTTON_ICON_HEIGHT), PANEL_BUTTON_ICON_X_OFFSET * col_order};
}

void ButtonsController::renderPanelTexture() {
    // Now we render the main texture with only the background images and the main buttons
    // Load background image
    Area srcArea(0, 0, this->screen_width, this->screen_height);
    Area destArea(0, 0, this->screen_width, this->screen_height);
    client_sprites_supplier[PANEL_BACKGROUND]->render(srcArea, destArea);

    // Load background image for optional buttons
    srcArea = Area(0, 0, PANEL_BUTTON_ICON_WIDTH * 2, PANEL_BUTTON_ICON_HEIGHT * PANEL_BUTTON_ICONS_ROWS_QUANTITY);
    destArea = Area(PANEL_BUTTON_ICON_X_OFFSET, PANEL_BUTTON_ICON_Y_OFFSET, PANEL_BUTTON_ICON_WIDTH * 2,
                    PANEL_BUTTON_ICON_HEIGHT * PANEL_BUTTON_ICONS_ROWS_QUANTITY);
    client_sprites_supplier[PANEL_BUTTONS_BACKGROUND]->render(srcArea, destArea);
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

void ButtonsController::locateButtons() {
    int row = 1;
    int column = 1;

    std::for_each(available_buttons.begin(), available_buttons.end(), [this, &row, &column](PanelButton *button) {
        if (row >= PANEL_BUTTON_ICONS_ROWS_QUANTITY) {
            // Move to the second column
            column = 2;
        }
        button->locate(getGlobalPosition(buildOptionalButtonRelativePosition(row, column)));
        row++;
    });
}

void ButtonsController::updateAvailableObjects(const std::vector<std::string>& available_objects) {
    // First we invalidate the current objects, we'll refresh them with the new ones
    std::for_each(available_buttons.begin(), available_buttons.end(), [](PanelButton *button) {
       button->setInvalid();
    });

    std::for_each(available_objects.begin(), available_objects.end(), [this](const std::string& object) {
        auto it = std::find_if(available_buttons.begin(), available_buttons.end(), [object](PanelButton *button) {
            return (button->getName() == object);
        });
        if (it == available_buttons.end()) {
            // New object
            available_buttons.push_back(ButtonsFactory::createButton(object, client_sprites_supplier));
            pending_changes = true;
        } else {
            (*it)->setValid();
        }
    });

    // Delete the invalid ones
    for (auto it = available_buttons.begin(); it != available_buttons.end(); it++) {
        if (!(*it)->isValid()) {
            pending_changes = true;
            delete *it;
            available_buttons.erase(it);
        }
    }

    // Now must locate all the buttons in the screen
    if (pending_changes) {
        locateButtons();
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
            return (button->getName() == picturable.name);
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
