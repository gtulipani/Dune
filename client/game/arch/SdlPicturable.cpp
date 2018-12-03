#include "SdlPicturable.h"

// STL Libraries
#include <iostream>

// Commons Libraries
#include <TileUtils.h>
#include <UnitsAndBuildings.h>

// Client Libraries
#include "Area.h"

#define PICTURABLE_WIDTH 90
#define PICTURABLE_HEIGHT 90

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
        sprites_supplier(sprites_supplier) {
    if (sdlTexture == nullptr) {
        std::cout << "Constructing SdlPicturable with texture null!" << std::endl;
    }
}

SdlPicturable::SdlPicturable(SdlPicturable &&other) noexcept : SdlPicturable(
        std::move(other.picturable),
        other.main_texture,
        other.sprites_supplier) {
    if (other.main_texture == nullptr) {
        std::cout << "Copy from null texture!" << std::endl;
    }
}

SdlPicturable &SdlPicturable::operator=(SdlPicturable &&other) noexcept {
    if (this == &other) {
        return *this; // other is myself!
    }

    if (other.main_texture == nullptr) {
        std::cout << "Movement from null texture!" << std::endl;
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

void SdlPicturable::render(int offset_x, int offset_y, int limit_col, int limit_row) {
    int originPicturableWidth = PICTURABLE_WIDTH;
    int originPicturableHeight = PICTURABLE_HEIGHT;

    int originSelectionSquareWidth = SELECTION_SQUARE_WIDTH;
    int originSelectionSquareHeight = SELECTION_SQUARE_HEIGHT;

    int originHealthBarWidth = HEALTH_BAR_WIDTH;
    int originHealthBarHeight = HEALTH_BAR_HEIGHT;

    int destinyWidth = this->picturable.size.col;
    int destinyHeight = this->picturable.size.row;

    int position_row = picturable.position.row + offset_y;
    int position_col = picturable.position.col + offset_x;

    // Where will the images be printed
    int picturable_destiny_row = position_row;
    int picturable_destiny_col = position_col;
    int selection_square_destiny_row = position_row;
    int selection_square_destiny_col = position_col;
    int health_bar_destiny_row = position_row - (TILE_PIXEL_RATE / 4);
    int health_bar_destiny_col = position_col;

    // Offset from origin images
    int picturable_origin_row_offset = 0;
    int health_bar_origin_row_offset = 0;
    int selection_square_origin_row_offset = 0;

    if (((position_col) >= limit_col) || ((position_row + picturable.size.row) <= limit_row)) {
        // Outside the limits, don't render anything
        return;
    } else {
        if ((position_col + picturable.size.col) >= limit_col) {
            // A portion of the width from the image is displayed and the other part isn't
            destinyWidth = (limit_col - position_col);

            // Display rate from the image
            float displayRate = (static_cast<float>(destinyWidth) / picturable.size.col);

            originPicturableWidth = static_cast<int>(displayRate * PICTURABLE_WIDTH);
            originSelectionSquareWidth = static_cast<int>(displayRate * SELECTION_SQUARE_WIDTH);
            originHealthBarWidth = static_cast<int>(displayRate * HEALTH_BAR_WIDTH);
        }
        // If (offset_y + position) is between (limit_row - size) and limit_row then it's displayed partially
        if ((position_row > (limit_row - picturable.size.row)) &&
                (position_row < limit_row)) {
            // A portion of the height from the image is displayed and the other part isn't
            destinyHeight = picturable.size.row + position_row - limit_row;

            // Display rate from the image
            float displayRate = (static_cast<float>(destinyHeight) / picturable.size.row);

            originPicturableHeight = static_cast<int>(displayRate * PICTURABLE_HEIGHT);
            originSelectionSquareHeight = static_cast<int>(displayRate * SELECTION_SQUARE_HEIGHT);
            originHealthBarHeight = static_cast<int>(displayRate * HEALTH_BAR_HEIGHT);

            // The image will be cutted from up down
            picturable_origin_row_offset = (PICTURABLE_HEIGHT - originPicturableHeight);
            selection_square_origin_row_offset = (SELECTION_SQUARE_HEIGHT - originSelectionSquareHeight);
            health_bar_origin_row_offset = (HEALTH_BAR_HEIGHT - originHealthBarHeight);

            // All the images will be offseted
            picturable_destiny_row = limit_row;
            selection_square_destiny_row = limit_row;
            health_bar_destiny_row = limit_row;
        }
    }

    Area picturableSrcArea(0, picturable_origin_row_offset, originPicturableWidth, originPicturableHeight);
    Area picturableDestArea(picturable_destiny_col, picturable_destiny_row, destinyWidth, destinyHeight);
    if (main_texture == nullptr) {
        std::cout << "Trying to render texture null!" << std::endl;
    } else {
        main_texture->render(picturableSrcArea, picturableDestArea);
    }

    if (this->picturable.selected) {
        // We must render the selection_square
        Area selectionSquareSrcArea(0, selection_square_origin_row_offset, originSelectionSquareWidth, originSelectionSquareHeight);
        Area selectionSquareDestArea(selection_square_destiny_col, selection_square_destiny_row, destinyWidth, destinyHeight);
        sprites_supplier[SELECTION_SQUARE]->render(selectionSquareSrcArea, selectionSquareDestArea);

        // We must render the health_bar
        Area healthBarSrcArea(0, health_bar_origin_row_offset, originHealthBarWidth, originHealthBarHeight);
        Area healthBarDestArea(health_bar_destiny_col, health_bar_destiny_row, destinyWidth, (TILE_PIXEL_RATE / 6));
        getHealthBarTexture()->render(healthBarSrcArea, healthBarDestArea);
    }
}

void SdlPicturable::update(Picturable picturable, SdlTexture *sdlTexture) {
    if (sdlTexture == nullptr) {
        std::cout << "Updating texture to null!" << std::endl;
    }
    this->picturable = std::move(picturable);
    this->main_texture = sdlTexture;
}

bool SdlPicturable::hasPriority() const {
    return (picturable.name == ESPECIA);
}

SdlTexture *SdlPicturable::getHealthBarTexture() {
    float health_rate = (static_cast<float>(this->picturable.health) / static_cast<float>(this->picturable.max_health));
    if (health_rate > 0.9) {
        return sprites_supplier[HEALTH_100];
    }
    if (health_rate > 0.8) {
        return sprites_supplier[HEALTH_90];
    }
    if (health_rate > 0.7) {
        return sprites_supplier[HEALTH_80];
    }
    if (health_rate > 0.6) {
        return sprites_supplier[HEALTH_70];
    }
    if (health_rate > 0.5) {
        return sprites_supplier[HEALTH_60];
    }
    if (health_rate > 0.4) {
        return sprites_supplier[HEALTH_50];
    }
    if (health_rate > 0.3) {
        return sprites_supplier[HEALTH_40];
    }
    if (health_rate > 0.2) {
        return sprites_supplier[HEALTH_30];
    }
    if (health_rate > 0.1) {
        return sprites_supplier[HEALTH_20];
    }
    return sprites_supplier[HEALTH_10];
}
