#include "SdlPicturable.h"

#include "Area.h"

SdlPicturable::SdlPicturable(Picturable picturable, SdlTexture sdlTexture) :
    picturable(std::move(picturable)),
    sdlTexture(std::move(sdlTexture)) {}

SdlPicturable::SdlPicturable(const SdlPicturable &other) : SdlPicturable(
        other.picturable,
        other.sdlTexture) {}

SdlPicturable::SdlPicturable(SdlPicturable &&other) noexcept : SdlPicturable(
        std::move(other.picturable),
        std::move(other.sdlTexture)) {}

SdlPicturable &SdlPicturable::operator=(const SdlPicturable &other) {
    if (this == &other) {
        return *this; // other is myself!
    }

    // Copy values
    this->picturable = other.picturable;
    this->sdlTexture = other.sdlTexture;

    return *this;
}

SdlPicturable &SdlPicturable::operator=(SdlPicturable &&other) noexcept {
    if (this == &other) {
        return *this; // other is myself!
    }

    // Copy values
    this->picturable = std::move(other.picturable);
    this->sdlTexture = std::move(other.sdlTexture);

    return *this;
}

void SdlPicturable::render() {
    // Still missing some work. Probably should migrate the movement to a different class called Camera or something similar
    Area srcArea(0, 0, 10, 10);
    Area destArea((10 * picturable.position.col), (10 * picturable.position.row), 10, 10);
    sdlTexture.render(srcArea, destArea);
}
