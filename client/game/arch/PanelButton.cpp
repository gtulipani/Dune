#include "PanelButton.h"
#include "Area.h"

#define BUTTON_ORIGINAL_WIDTH 80
#define BUTTON_ORIGINAL_HEIGHT 80

PanelButton::PanelButton(int width, int height, Point screen_position, std::string action, SdlTexture texture) :
        width(width),
        height(height),
        screen_position(std::move(screen_position)),
        action(std::move(action)),
        texture(std::move(texture)) {}

PanelButton::PanelButton(int width, int height, Point screen_position, std::string action, std::string image_path, SdlWindow *window)
        : PanelButton(
        width,
        height,
        std::move(screen_position),
        std::move(action),
        SdlTexture(image_path, window)) {}

void PanelButton::render(int offset_x, int offset_y) {
    Area srcArea(0, 0, BUTTON_ORIGINAL_WIDTH, BUTTON_ORIGINAL_HEIGHT);
    Area destArea(offset_x + this->screen_position.col, offset_y + this->screen_position.row, this->width,
                  this->height);
    this->texture.render(srcArea, destArea);
}

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
