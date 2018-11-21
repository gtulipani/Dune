#include <iostream>
#include <TileUtils.h>
#include "SdlPicturable.h"

#include "Area.h"

#define PICTURABLE_WIDTH 80
#define PICTURABLE_HEIGHT 80

#define HEALTH_BAR_WIDTH 400
#define HEALTH_BAR_HEIGHT 100

#define SELECTION_SQUARE_WIDTH 400
#define SELECTION_SQUARE_HEIGHT 400

int SdlPicturable::recalculateWidth(int destinyWidth, int originalWidth) {
    // Calculate how much of the original image we'll render
    float displayRate = (static_cast<float>(destinyWidth)/originalWidth);

    // We identify how much of the original image we must render
    return static_cast<int>(displayRate * originalWidth);
}

SdlPicturable::SdlPicturable(Picturable picturable, SdlTexture *sdlTexture, ClientSpritesSupplier &sprites_supplier) :
    picturable(std::move(picturable)),
    main_texture(sdlTexture),
    sprites_supplier(sprites_supplier) {}

SdlPicturable::SdlPicturable(SdlPicturable &&other) noexcept : SdlPicturable(
        std::move(other.picturable),
        other.main_texture,
        other.sprites_supplier) {}

SdlPicturable &SdlPicturable::operator=(SdlPicturable &&other) noexcept {
    if (this == &other) {
        return *this; // other is myself!
    }

    // Copy values
    this->picturable = std::move(other.picturable);
    this->main_texture = other.main_texture;
    this->sprites_supplier = std::move(other.sprites_supplier);

    other.main_texture = nullptr;

    return *this;
}

bool SdlPicturable::operator==(const Picturable& other) const {
    return other.id == this->picturable.id;
}

void SdlPicturable::render(int offset_x, int offset_y, int limit_column) {
    int originPicturableWidth = PICTURABLE_WIDTH;
    int originPicturableHeight = PICTURABLE_HEIGHT;

    int originSelectionSquareWidth = SELECTION_SQUARE_WIDTH;
    int originSelectionSquareHeight = SELECTION_SQUARE_HEIGHT;

    int originHealthBarWidth = HEALTH_BAR_WIDTH;
    int originHealthBarHeight = HEALTH_BAR_HEIGHT;

    int destinyWidth = this->picturable.size.col;
    int destinyHeight = this->picturable.size.row;

    if ((offset_x + picturable.position.col) >= limit_column) {
        // Outside the limits, don't render anything
        return;
    } else if ((offset_x + picturable.position.col + this->picturable.size.col) >= limit_column) {
        // A portion of the image is displayed and the other part isn't
        destinyWidth = (limit_column - offset_x - picturable.position.col);

        originPicturableWidth = recalculateWidth(destinyWidth, this->picturable.size.col);
        originSelectionSquareWidth = recalculateWidth(destinyWidth, SELECTION_SQUARE_WIDTH);
        originHealthBarWidth = recalculateWidth(destinyWidth, HEALTH_BAR_WIDTH);
    }

    Area picturableSrcArea(0, 0, originPicturableWidth, originPicturableHeight);
    Area picturableDestArea((picturable.position.col) + offset_x, (picturable.position.row) + offset_y, destinyWidth, destinyHeight);
    main_texture->render(picturableSrcArea, picturableDestArea);

    if (this->picturable.selected) {
        // We must render the selection_square
        Area selectionSquareSrcArea(0, 0, originSelectionSquareWidth, originSelectionSquareHeight);
        Area selectionSquareDestArea((picturable.position.col) + offset_x, (picturable.position.row) + offset_y, destinyWidth, destinyHeight);
        sprites_supplier[SELECTION_SQUARE]->render(selectionSquareSrcArea, selectionSquareDestArea);

        // We must render the health_bar
        // We'll eventually use the percentage of age, hardcoding 100% as for now
        Area healthBarSrcArea(0, 0, originHealthBarWidth, originHealthBarHeight);
        Area healthBarDestArea((picturable.position.col) + offset_x, (picturable.position.row) + offset_y - (TILE_PIXEL_RATE / 5), destinyWidth, (TILE_PIXEL_RATE / 6));
        sprites_supplier[HEALTH_100]->render(healthBarSrcArea, healthBarDestArea);
    }
}

void SdlPicturable::update(Picturable picturable, SdlTexture *sdlTexture) {
    this->picturable = std::move(picturable);
    this->main_texture = sdlTexture;
}
