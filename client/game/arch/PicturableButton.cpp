#include "PicturableButton.h"

// Client Libraries
#include "Area.h"
#include "RequiresTerrainControllerActionException.h"

PicturableButton::PicturableButton(int width,
                       int height,
                       Point screen_position,
                       std::vector<int> actions,
                       SdlTexture* texture,
                       ClientSpritesSupplier &sprites_supplier,
                       bool requires_second_action) : PanelButton(
        width,
        height,
        std::move(screen_position),
        std::move(actions),
        texture,
        sprites_supplier),
        requires_second_action(requires_second_action),
        is_being_created(false),
        progress(100) {}

PicturableButton::PicturableButton(int width,
                       int height,
                       Point screen_position,
                       std::vector<int> actions,
                       std::string image_path,
                       SdlWindow *window,
                       ClientSpritesSupplier &sprites_supplier,
                       bool requires_second_action) : PicturableButton(
        width,
        height,
        std::move(screen_position),
        std::move(actions),
        new SdlTexture(image_path, window),
        sprites_supplier,
        requires_second_action) {}

void PicturableButton::render(int offset_x, int offset_y) {
    Area srcArea(0, 0, BUTTON_ORIGINAL_WIDTH, BUTTON_ORIGINAL_HEIGHT);
    Area destArea(offset_x + screen_position.col, offset_y + screen_position.row, width, height);
    texture->render(srcArea, destArea);
    if (is_being_created) {
        getProgressTexture()->render(srcArea, destArea);
    }
    have_I_changed = false;
}

SdlTexture* PicturableButton::getProgressTexture() {
    if (this->progress == 100) {
        return sprites_supplier[CONSTRUCTION_PERCENTAGE_100];
    }
    if (this->progress >= 87) {
        return sprites_supplier[CONSTRUCTION_PERCENTAGE_87];
    }
    if (this->progress >= 75) {
        return sprites_supplier[CONSTRUCTION_PERCENTAGE_75];
    }
    if (this->progress >= 62) {
        return sprites_supplier[CONSTRUCTION_PERCENTAGE_62];
    }
    if (this->progress >= 50) {
        return sprites_supplier[CONSTRUCTION_PERCENTAGE_50];
    }
    if (this->progress >= 37) {
        return sprites_supplier[CONSTRUCTION_PERCENTAGE_37];
    }
    if (this->progress >= 25) {
        return sprites_supplier[CONSTRUCTION_PERCENTAGE_25];
    }
    if (this->progress >= 12) {
        return sprites_supplier[CONSTRUCTION_PERCENTAGE_12];
    }
    return sprites_supplier[CONSTRUCTION_PERCENTAGE_0];
}

void PicturableButton::click(EventsLooperThread* processer, std::function<void(EventsLooperThread*, int, std::vector<int>, Point, Point)> push_function) {
    if (!is_being_created) {
        // If it's not during creation, then it can be clicked
        if (requires_second_action) {
            // Action has already been applied therefore I need a second_action
            throw RequiresTerrainControllerActionException();
        } else {
            // Pushes first action with the function received as parameter
            push_function(processer, actions[0], {0}, screen_position, screen_position);
            disable();
        }
    }
}

void PicturableButton::disable() {
    is_being_created = true;
    progress = 0;
    have_I_changed = true;
}

void PicturableButton::resolve(Point position, EventsLooperThread *processer, std::function<void(EventsLooperThread *, int, std::vector<int>, Point, Point)> push_function) {
    push_function(processer, actions[1], {0}, std::move(position), Point(0,0));
}

bool PicturableButton::hasPendingAction() {
    return requires_second_action;
}
