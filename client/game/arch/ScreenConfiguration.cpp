#include "ScreenConfiguration.h"

ScreenConfiguration::ScreenConfiguration(int width, int height, int width_offset, int height_offset) :
    width(width),
    height(height),
    width_offset(width_offset),
    height_offset(height_offset) {}

ScreenConfiguration::ScreenConfiguration(const ScreenConfiguration &other) : ScreenConfiguration(
        other.width,
        other.height,
        other.width_offset,
        other.height_offset) {}

ScreenConfiguration::ScreenConfiguration(ScreenConfiguration &&other) noexcept : ScreenConfiguration(
        other.width,
        other.height,
        other.width_offset,
        other.height_offset) {
    other.width= 0;
    other.height = 0;
    other.width_offset = 0;
    other.height_offset = 0;
}

ScreenConfiguration &ScreenConfiguration::operator=(const ScreenConfiguration &other) {
    if (this == &other) {
        return *this; // other is myself!
    }

    // Copy values
    this->width = other.width;
    this->height = other.height;
    this->width_offset = other.width_offset;
    this->height_offset = other.height_offset;

    return *this;
}

ScreenConfiguration &ScreenConfiguration::operator=(ScreenConfiguration &&other) noexcept {
    if (this == &other) {
        return *this; // other is myself!
    }

    // Copy values
    this->width = other.width;
    this->height = other.height;
    this->width_offset = other.width_offset;
    this->height_offset = other.height_offset;

    other.width = 0;
    other.height= 0;
    other.width_offset = 0;
    other.height_offset= 0;

    return *this;
}

int ScreenConfiguration::getWidth() const {
    return width;
}

int ScreenConfiguration::getHeight() const {
    return height;
}

int ScreenConfiguration::getWidthOffset() const {
    return width_offset;
}

int ScreenConfiguration::getHeightOffset() const {
    return height_offset;
}
