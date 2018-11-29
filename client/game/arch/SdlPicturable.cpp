#include "SdlPicturable.h"

// STL Libraries
#include <iostream>

// Commons Libraries
#include <TileUtils.h>
#include <UnitsAndBuildings.h>

// Client Libraries
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

        // Display rate from the image
        float displayRate = (static_cast<float>(destinyWidth)/this->picturable.size.col);

        originPicturableWidth = static_cast<int>(displayRate * this->picturable.size.col);
        originSelectionSquareWidth = static_cast<int>(displayRate * SELECTION_SQUARE_WIDTH);
        originHealthBarWidth = static_cast<int>(displayRate * HEALTH_BAR_WIDTH);
    }

    Area picturableSrcArea(0, 0, originPicturableWidth, originPicturableHeight);
    Area picturableDestArea((picturable.position.col) + offset_x, (picturable.position.row) + offset_y, destinyWidth, destinyHeight);
    if (main_texture == nullptr) {
        std::cout << "Trying to render texture null!" << std::endl;
    } else {
        main_texture->render(picturableSrcArea, picturableDestArea);
    }

    if (this->picturable.selected) {
        // We must render the selection_square
        Area selectionSquareSrcArea(0, 0, originSelectionSquareWidth, originSelectionSquareHeight);
        Area selectionSquareDestArea((picturable.position.col) + offset_x, (picturable.position.row) + offset_y, destinyWidth, destinyHeight);
        sprites_supplier[SELECTION_SQUARE]->render(selectionSquareSrcArea, selectionSquareDestArea);

        // We must render the health_bar
        // We'll eventually use the percentage of age, hardcoding 100% as for now
        Area healthBarSrcArea(0, 0, originHealthBarWidth, originHealthBarHeight);
        Area healthBarDestArea((picturable.position.col) + offset_x, (picturable.position.row) + offset_y - (TILE_PIXEL_RATE / 4), destinyWidth, (TILE_PIXEL_RATE / 6));
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
