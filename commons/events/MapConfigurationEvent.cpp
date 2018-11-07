#include "MapConfigurationEvent.h"

MapConfigurationEvent::MapConfigurationEvent(Matrix matrix) :
        matrix(std::move(matrix)) {}

MapConfigurationEvent::MapConfigurationEvent(const MapConfigurationEvent &other) : MapConfigurationEvent(
        other.matrix) {}

MapConfigurationEvent::MapConfigurationEvent(MapConfigurationEvent &&other) noexcept : MapConfigurationEvent(
        std::move(other.matrix)) {}

MapConfigurationEvent &MapConfigurationEvent::operator=(const MapConfigurationEvent &other) {
    if (this == &other) {
        return *this; // other is myself!
    }

    // Copy values
    this->matrix = other.matrix;

    return *this;
}

MapConfigurationEvent &MapConfigurationEvent::operator=(MapConfigurationEvent &&other) noexcept {
    if (this == &other) {
        return *this; // other is myself!
    }

    // Copy values
    this->matrix = std::move(other.matrix);

    return *this;
}
