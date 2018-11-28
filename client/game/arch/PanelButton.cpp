#include "PanelButton.h"
#include "Area.h"

PanelButton::PanelButton(int width,
                         int height,
                         Point screen_position,
                         std::vector<int> actions,
                         SdlTexture* texture,
                         ClientSpritesSupplier &sprites_supplier) :
        width(width),
        height(height),
        screen_position(std::move(screen_position)),
        actions(std::move(actions)),
        texture(texture),
        sprites_supplier(sprites_supplier),
        have_I_changed(false) {}

PanelButton::PanelButton(int width,
                         int height,
                         Point screen_position,
                         std::vector<int> actions,
                         std::string image_path,
                         SdlWindow *window,
                         ClientSpritesSupplier &sprites_supplier)
        : PanelButton(
        width,
        height,
        std::move(screen_position),
        std::move(actions),
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
    return !actions.empty();
}

bool PanelButton::hasChanged() const {
    return have_I_changed;
}

PanelButton::~PanelButton() = default;
