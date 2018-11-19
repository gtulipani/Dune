#include "PanelButton.h"
#include "Area.h"

#define BUTTON_ORIGINAL_WIDTH 80
#define BUTTON_ORIGINAL_HEIGHT 80

PanelButton::PanelButton(int id, int width, int height, SdlTexture texture) :
    id(id),
    width(width),
    height(height),
    texture(std::move(texture)) {}

PanelButton::PanelButton(int id, int width, int height, std::string image_path, SdlWindow* window) : PanelButton(
        id,
        width,
        height,
        SdlTexture(image_path, window)) {}

void PanelButton::render(int offset_x, int offset_y) {
    Area srcArea(0, 0, BUTTON_ORIGINAL_WIDTH, BUTTON_ORIGINAL_HEIGHT);
    Area destArea(offset_x + (this->id * this->width), offset_y, this->width, this->height);
    this->texture.render(srcArea, destArea);
}