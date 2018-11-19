#include "PanelButton.h"
#include "Area.h"

#define BUTTON_ORIGINAL_WIDTH 80
#define BUTTON_ORIGINAL_HEIGHT 80

PanelButton::PanelButton(int width, int height, Point screen_position, SdlTexture texture) :
    width(width),
    height(height),
    screen_position(std::move(screen_position)),
    texture(std::move(texture)) {}

PanelButton::PanelButton(int width, int height, Point screen_position, std::string image_path, SdlWindow* window) : PanelButton(
        width,
        height,
        std::move(screen_position),
        SdlTexture(image_path, window)) {}

void PanelButton::render(int offset_x, int offset_y) {
    Area srcArea(0, 0, BUTTON_ORIGINAL_WIDTH, BUTTON_ORIGINAL_HEIGHT);
    Area destArea(offset_x + this->screen_position.col, offset_y + this->screen_position.row, this->width, this->height);
    this->texture.render(srcArea, destArea);
}
