#include "ButtonsController.h"

// STL Libraries
#include <algorithm>
#include <utility>

// Commons Libraries
#include <events/ClientEvent.h>
#include <events/GameStatusEvent.h>
#include <UnitsAndBuildings.h>

// SDL Libraries
#include <SDL_events.h>
#include <Sprites.h>

// Client Libraries
#include "../buttons/UnitButton.h"
#include "../buttons/BuildingButton.h"
#include "../buttons/ButtonsFactory.h"
#include "RequiresExternalControllerActionException.h"
#include "ScreenController.h"

ButtonsController::ButtonsController(SdlWindow *window, ClientSpritesSupplier &client_sprites_supplier, const ScreenConfiguration& screen_configuration) : Controller(
        window,
        screen_configuration,
        true),
        client_sprites_supplier(client_sprites_supplier),
        clicked(false),
        panel_rendered(false) {
    buildTerrainTexture();
}

void ButtonsController::buildTerrainTexture() {
    panel_texture = new SdlTexture(screen_configuration.getWidth(), screen_configuration.getHeight(), this->window->getRenderer());
    panel_texture->setAsTarget();

    buildPanelTexture();

    window->render();
    window->setAsTarget();
}

Point ButtonsController::getGlobalPosition(Point point) {
    return {point.row, point.col + screen_configuration.getWidthOffset()};
}

Point ButtonsController::getRelativePosition(Point point) {
    return {point.row, point.col - screen_configuration.getWidthOffset()};
}

Point ButtonsController::buildOptionalButtonRelativePosition(int row_order, int col_order) {
    // Order starts from zero
    return {PANEL_BUTTON_ICON_Y_OFFSET + ((row_order - 1) * PANEL_BUTTON_ICON_HEIGHT), PANEL_BUTTON_ICON_X_OFFSET * col_order};
}

void ButtonsController::buildPanelTexture() {
    // Now we render the main texture with only the background images and the main buttons
    // Load background image
    Area srcArea(0, 0, screen_configuration.getWidth(), screen_configuration.getHeight());
    Area destArea(0, 0, screen_configuration.getWidth(), screen_configuration.getHeight());
    client_sprites_supplier[PANEL_BACKGROUND]->render(srcArea, destArea);
}

void ButtonsController::renderPanel() {
    if (!panel_rendered) {
        // Render the main texture containing the background image and the main buttons
        Area srcArea(0, 0, screen_configuration.getWidth(), screen_configuration.getHeight());
        Area destArea(screen_configuration.getWidthOffset(), 0, screen_configuration.getWidth(), screen_configuration.getHeight());
        panel_texture->render(srcArea, destArea);

        window->render();
        panel_rendered = true;
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

void ButtonsController::update(const GameStatusEvent &event) {
    // Append both picturables and selectables
    std::vector<Picturable> picturables(event.picturables);
    picturables.insert(
            std::end(picturables),
            std::begin(event.selectedObjects),
            std::end(event.selectedObjects));

    updateAvailableObjects(event.availableObjects);
    processPicturables(picturables);
}

void ButtonsController::render() {
    renderPanel();

    // Load background image for optional buttons
    Area srcArea = Area(0, 0, PANEL_BUTTON_ICON_WIDTH * 2, PANEL_BUTTON_ICON_HEIGHT * PANEL_BUTTON_ICONS_ROWS_QUANTITY);
    Area destArea = Area(screen_configuration.getWidthOffset() + PANEL_BUTTON_ICON_X_OFFSET, PANEL_BUTTON_ICON_Y_OFFSET, PANEL_BUTTON_ICON_WIDTH * 2,
                         PANEL_BUTTON_ICON_HEIGHT * PANEL_BUTTON_ICONS_ROWS_QUANTITY);
    client_sprites_supplier[PANEL_BUTTONS_BACKGROUND]->render(srcArea, destArea);

    // Render each one of the available buttons
    std::for_each(available_buttons.begin(), available_buttons.end(), [&](PanelButton *button) {
        button->render(0, 0);
    });

    window->render();
    pending_changes = false;
}

void ButtonsController::move(enum Movement movement) {}

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

bool ButtonsController::resolvePendingAction(const SDL_MouseButtonEvent &mouse_event, EventsLooperThread *processer, const std::function<void(EventsLooperThread *, int, int, Point, Point)>& push_function) {
    clicked = false;
    bool resolved = false;
    if (notIncludes(mouse_event.x, mouse_event.y)) {
        // Recheck if was clicked in the correct place (not in the panel)
        Point position(mouse_event.y, mouse_event.x); // Review this, it's not taking offset into account
        switch (mouse_event.button) {
            case SDL_BUTTON_LEFT: {
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
                break;
            }
            case SDL_BUTTON_RIGHT: {
                break;
            }
            default:
                break;
        }
    }
    return resolved;
}
void ButtonsController::parseMouseClick(const SDL_MouseButtonEvent &mouse_event, EventsLooperThread *processer, const std::function<void(EventsLooperThread *, int, int, Point, Point)>& push_function) {
    clicked = includes(mouse_event.x, mouse_event.y);
}
void ButtonsController::parseMouseRelease(const SDL_MouseButtonEvent &mouse_event, EventsLooperThread *processer, const std::function<void(EventsLooperThread *, int, int, Point, Point)>& push_function) {
    if (clicked) {
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
    clicked = false;
}

ButtonsController::~ButtonsController() {
    // Delete main texture
    delete panel_texture;

    // Delete buttons
    for (auto &button : this->available_buttons) {
        delete button;
    }
}
