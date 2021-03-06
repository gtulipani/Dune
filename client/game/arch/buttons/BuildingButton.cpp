#include "BuildingButton.h"

// Client Libraries
#include "../Area.h"
#include "../controllers/RequiresExternalControllerActionException.h"

BuildingButton::BuildingButton(int width,
                               int height,
                               const std::string& type,
                               int icon_type,
                               std::vector<int> actions,
                               ClientSpritesSupplier &sprites_supplier) : PanelButton(
        width,
        height,
        type,
        sprites_supplier[icon_type],
        std::move(actions),
        sprites_supplier) {}

BuildingButton::BuildingButton(int width,
                               int height,
                               const std::string& type,
                               SdlTexture *texture,
                               std::vector<int> actions,
                               ClientSpritesSupplier &sprites_supplier) : PanelButton(
        width,
        height,
        type,
        texture,
        std::move(actions),
        sprites_supplier) {}

void BuildingButton::click(EventsLooperThread* processer, std::function<void(EventsLooperThread*, int, int, Point, Point)> push_function) {
    if (!is_being_created) {
        // If it's not during creation, then it can be clicked
        if (finished_creating) {
            // Action has already been applied therefore I need a second_action
            throw RequiresExternalControllerActionException();
        } else {
            // Pushes first action with the function received as parameter
            push_function(processer, actions[0], 0, screen_position, screen_position);
            disable();
        }
    }
}

void BuildingButton::resolve(const Point& position, EventsLooperThread *processer, std::function<void(EventsLooperThread *, int, int, Point, Point)> push_function) {
    push_function(processer, actions[1], picturable_id, position, position);
}

bool BuildingButton::isWaitingForAction() const {
    return finished_creating;
}
