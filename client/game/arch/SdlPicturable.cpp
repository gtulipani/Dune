#include "SdlPicturable.h"

#include "Area.h"

#define PICTURABLE_WIDTH 80
#define PICTURABLE_HEIGHT 80

SdlPicturable::SdlPicturable(Picturable picturable, SdlTexture &sdlTexture, int width, int height) :
    picturable(std::move(picturable)),
    sdlTexture(sdlTexture),
    width(width),
    height(height) {}

SdlPicturable::SdlPicturable(SdlPicturable &&other) noexcept : SdlPicturable(
        std::move(other.picturable),
        other.sdlTexture,
        other.width,
        other.height) {}

SdlPicturable &SdlPicturable::operator=(SdlPicturable &&other) noexcept {
    if (this == &other) {
        return *this; // other is myself!
    }

    // Copy values
    this->picturable = std::move(other.picturable);
    this->sdlTexture = other.sdlTexture;
    this->width = other.width;
    this->height = other.height;

    return *this;
}

bool SdlPicturable::operator==(const Picturable& other) const {
    return other.id == this->picturable.id;
}

void SdlPicturable::render(int offset_x, int offset_y) {
    // Still missing some work. Probably should migrate the movement to a different class called Camera or something similar
    Area srcArea(0, 0, PICTURABLE_WIDTH, PICTURABLE_HEIGHT);
    Area destArea((picturable.position.col) + offset_x, (picturable.position.row) + offset_y, this->width, this->height);
    sdlTexture.render(srcArea, destArea);
}
