#include "PanelButton.h"
#include "Area.h"

PanelButton::PanelButton(int width,
                         int height,
                         Point screen_position,
                         std::string action,
                         SdlTexture* texture,
                         ClientSpritesSupplier &sprites_supplier) :
        width(width),
        height(height),
        screen_position(std::move(screen_position)),
        action(std::move(action)),
        texture(texture),
        sprites_supplier(sprites_supplier) {}

PanelButton::PanelButton(int width,
                         int height,
                         Point screen_position,
                         std::string action,
                         std::string image_path,
                         SdlWindow *window,
                         ClientSpritesSupplier &sprites_supplier)
        : PanelButton(
        width,
        height,
        std::move(screen_position),
        std::move(action),
        new SdlTexture(image_path, window),
        sprites_supplier) {}

bool PanelButton::includesPosition(Point point) const {
    // Returns true if the point received as parameter is contained inside the limit determined by the
    // screen_position, the width and the height
    return
            ((this->screen_position.col <= point.col) &&
             (point.col <= (this->screen_position.col + this->width)) &&
             (this->screen_position.row <= point.row) &&
             (point.row <= (this->screen_position.row + this->height)));
}

bool PanelButton::includesExternalAction() const {
    return !this->action.empty();
}

std::string PanelButton::getAction() const {
    return this->action;
}

PanelButton::~PanelButton() = default;
