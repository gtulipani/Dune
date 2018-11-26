#include "PicturableButton.h"

// Client Libraries
#include "Area.h"

PicturableButton::PicturableButton(int width,
                       int height,
                       Point screen_position,
                       std::string action,
                       SdlTexture* texture,
                       ClientSpritesSupplier &sprites_supplier) : PanelButton(
        width,
        height,
        std::move(screen_position),
        std::move(action),
        texture,
        sprites_supplier),
        can_be_clicked(true),
        progress(100) {}

PicturableButton::PicturableButton(int width,
                       int height,
                       Point screen_position,
                       std::string action,
                       std::string image_path,
                       SdlWindow *window,
                       ClientSpritesSupplier &sprites_supplier) : PicturableButton(
        width,
        height,
        std::move(screen_position),
        std::move(action),
        new SdlTexture(image_path, window),
        sprites_supplier) {}

void PicturableButton::render(int offset_x, int offset_y) {
    Area srcArea(0, 0, BUTTON_ORIGINAL_WIDTH, BUTTON_ORIGINAL_HEIGHT);
    Area destArea(offset_x + this->screen_position.col, offset_y + this->screen_position.row, this->width,
                  this->height);
    this->texture->render(srcArea, destArea);
    if (!this->can_be_clicked) {
        // If can't be clicked it means there is something going on. Requires a progress texture
        this->getProgressTexture()->render(srcArea, destArea);
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

void PicturableButton::click(EventsLooperThread* processer, std::function<void(EventsLooperThread*, std::string, Point, Point)> push_function) {
    if (can_be_clicked) {
        // Push the proper event
        push_function(processer, this->action, this->screen_position, this->screen_position);
        disable();
    }
}

void PicturableButton::disable() {
    can_be_clicked = false;
    progress = 0;
    have_I_changed = true;
}
