#include "SdlPicturable.h"

#include "Area.h"

#define PICTURABLE_SIZE 32

SdlPicturable::SdlPicturable(Picturable picturable, SdlTexture sdlTexture) :
    picturable(std::move(picturable)),
    sdlTexture(std::move(sdlTexture)) {}

SdlPicturable::SdlPicturable(SdlPicturable &&other) noexcept : SdlPicturable(
        std::move(other.picturable),
        std::move(other.sdlTexture)) {}

SdlPicturable &SdlPicturable::operator=(SdlPicturable &&other) noexcept {
    if (this == &other) {
        return *this; // other is myself!
    }

    // Copy values
    this->picturable = std::move(other.picturable);
    this->sdlTexture = std::move(other.sdlTexture);

    return *this;
}

void SdlPicturable::render(int offset_x, int offset_y) {
    // Still missing some work. Probably should migrate the movement to a different class called Camera or something similar
    Area srcArea(0, 0, PICTURABLE_SIZE, PICTURABLE_SIZE);
    Area destArea((/*PICTURABLE_SIZE * */picturable.position.col) + offset_x, (/*PICTURABLE_SIZE * */picturable.position.row) + offset_y, 32, 32);
    sdlTexture.render(srcArea, destArea);
}
