#ifndef __MAP_CONFIGURATION_EVENT_H__
#define __MAP_CONFIGURATION_EVENT_H__

#include "Matrix.h"

struct MapConfigurationEvent {
public:
    Matrix matrix{};

    MapConfigurationEvent() = default;

    explicit MapConfigurationEvent(Matrix matrix);

    MapConfigurationEvent(const MapConfigurationEvent &other);

    MapConfigurationEvent(MapConfigurationEvent &&other) noexcept;

    // Overloading the assignment by copy
    MapConfigurationEvent &operator=(const MapConfigurationEvent &other);

    // Overloading the assignment by movement
    MapConfigurationEvent &operator=(MapConfigurationEvent &&other) noexcept;
};


#endif //__MAP_CONFIGURATION_EVENT_H__
