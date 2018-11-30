#include <utility>

#include "WindowController.h"

// Commons Libraries
#include <TileUtils.h>
#include <TerrainType.h>
#include <events/GameStatusEvent.h>

// Client Libraries
#include "RequiresTerrainControllerActionException.h"
#include "ScreenController.h"

// SDL Libraries
#include <SDL_events.h>

#define WINDOW_WIDTH 1280
#define WINDOW_HEIGHT 720

WindowController::WindowController(SdlWindow* window) :
    window(window),
    client_sprites_supplier(window),
    status_controller(window, client_sprites_supplier),
    terrain_controller(window, client_sprites_supplier),
    buttons_controller(window, client_sprites_supplier, &terrain_controller, &TerrainController::renderEagleEye),
    pending_action(false) {}

WindowController::WindowController() : WindowController(
        new SdlWindow(WINDOW_WIDTH, WINDOW_HEIGHT, SCREEN_WIDTH, SCREEN_HEIGHT)) {}

void WindowController::configure(Matrix matrix) {
    window->fill();

    terrain_controller.configure(std::move(matrix), SCREEN_TERRAIN_WIDTH, SCREEN_HEIGHT, SCREEN_STATUS_HEIGHT);
    buttons_controller.configure(SCREEN_PANEL_WIDTH, SCREEN_PANEL_HEIGHT, SCREEN_TERRAIN_WIDTH);
    status_controller.configure(SCREEN_STATUS_WIDTH, SCREEN_STATUS_HEIGHT);
}

void WindowController::fill() {
    terrain_controller.fill();
}

void WindowController::refresh() {
    terrain_controller.refresh();
    buttons_controller.refresh();
    status_controller.refresh();
}

void WindowController::render() {
    terrain_controller.render();
    buttons_controller.render();
    status_controller.render();
}

void WindowController::move(enum Movement movement) {
    if (this->terrain_controller.move(movement)) {
        this->buttons_controller.move();
    }
}

void WindowController::parseMouseClick(SDL_MouseButtonEvent& mouse_event, EventsLooperThread* processer, std::function<void(EventsLooperThread*, int, int, Point, Point)> push_function) {
    if (mouse_event.x < SCREEN_TERRAIN_WIDTH) {
        // Store where does the Mouse Click take place
        last_click_event_occurrence = TERRAIN;
        terrain_controller.parseMouseClickButton(mouse_event);
    } else {
        // Store where does the Mouse Click take place
        last_click_event_occurrence = BUTTONS;
        buttons_controller.parseMouseClickButton(mouse_event, processer, std::move(push_function));
    }
}

void WindowController::parseMouseRelease(SDL_MouseButtonEvent& mouse_event, EventsLooperThread* processer, std::function<void(EventsLooperThread*, int, int, Point, Point)> push_function) {
    if (mouse_event.x < SCREEN_TERRAIN_WIDTH) {
        if (last_click_event_occurrence == BUTTONS) {
            // We clicked on the Panel Section and we released the mouse on the terrain section. Don't do anything
        } else {
            last_click_event_occurrence = NONE;
            if (pending_action) {
                // Resolve pending action
                if (buttons_controller.resolvePendingAction(mouse_event, processer, std::move(push_function))) {
                    pending_action = false;
                }
            } else {
                // Parse terrain event
                terrain_controller.parseMouseReleaseButton(mouse_event, processer, std::move(push_function));
                pending_action = false;
            }
        }
    } else {
        if (last_click_event_occurrence == TERRAIN) {
            // We clicked on the Terrain Section and we released the mouse on the buttons section. Don't do anything
        } else {
            last_click_event_occurrence = NONE;
            try {
                buttons_controller.parseMouseReleaseButton(mouse_event, processer, std::move(push_function));
            } catch (RequiresTerrainControllerActionException& e) {
                // Action in the TerrainController is required for the action to be completed
                pending_action = true;
            }

        }
    }
}

void WindowController::update(const GameStatusEvent &event) {
    processAvailableObjects(event.availableObjects);

    // Append both picturables and selectables
    std::vector<Picturable> picturables(event.picturables);
    picturables.insert(
            std::end(picturables),
            std::begin(event.selectedObjects),
            std::end(event.selectedObjects));

    processPicturables(picturables);

    status_controller.update(event);
}

void WindowController::processAvailableObjects(const std::vector<std::string> &available_objects) {
    this->buttons_controller.updateAvailableObjects(available_objects);
}

void WindowController::processPicturables(std::vector<Picturable>& picturables) {
    this->terrain_controller.processPicturables(picturables);
    this->buttons_controller.processPicturables(picturables);
}
