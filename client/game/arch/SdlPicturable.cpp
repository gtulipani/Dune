#include <iostream>
#include "SdlPicturable.h"

#include "Area.h"

#define PICTURABLE_WIDTH 80
#define PICTURABLE_HEIGHT 80

SdlPicturable::SdlPicturable(Picturable picturable, SdlTexture *sdlTexture) :
    picturable(std::move(picturable)),
    sdlTexture(sdlTexture) {}

SdlPicturable::SdlPicturable(SdlPicturable &&other) noexcept : SdlPicturable(
        std::move(other.picturable),
        other.sdlTexture) {}

SdlPicturable &SdlPicturable::operator=(SdlPicturable &&other) noexcept {
    if (this == &other) {
        return *this; // other is myself!
    }

    // Copy values
    this->picturable = std::move(other.picturable);
    this->sdlTexture = other.sdlTexture;

    other.sdlTexture = nullptr;

    return *this;
}

bool SdlPicturable::operator==(const Picturable& other) const {
    return other.id == this->picturable.id;
}

void SdlPicturable::render(int offset_x, int offset_y, int limit_column, int limit_row) {
    int originWidth = PICTURABLE_WIDTH;
    int originHeight = PICTURABLE_HEIGHT;
    int destinyWidth = this->picturable.size.col;
    int destinyHeight = this->picturable.size.row;

    if ((offset_x + picturable.position.col) >= limit_column) {
        // Outside the limits, don't render anything
        return;
    } else if ((offset_x + picturable.position.col + this->picturable.size.col) >= limit_column) {
        // A portion of the image is displayed and the other part isn't
        destinyWidth = (limit_column - offset_x - picturable.position.col);

        // We calculate how much of the image will be displayed
        float displayRate = (static_cast<float>(destinyWidth)/this->picturable.size.col);

        // We identify how much of the original image we must render
        originWidth = static_cast<int>(displayRate * picturable.size.col);
    }

    Area srcArea(0, 0, originWidth, originHeight);
    Area destArea((picturable.position.col) + offset_x, (picturable.position.row) + offset_y, destinyWidth, destinyHeight);
    sdlTexture->render(srcArea, destArea);
}

void SdlPicturable::update(Picturable picturable, SdlTexture *sdlTexture) {
    this->picturable = std::move(picturable);
    this->sdlTexture = sdlTexture;
}
