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
        sprites_supplier) {}

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
    sprites_supplier[CONSTRUCTION_PERCENTAGE_100]->render(srcArea, destArea);
}
