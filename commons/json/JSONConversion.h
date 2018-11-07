#ifndef __JSON__CONVERSION_H__
#define __JSON__CONVERSION_H__

#include <iostream>
#include "json.hpp"
#include "../events/ClientEvent.h"
#include "../events/MapConfigurationEvent.h"
#include "../events/GameStatusEvent.h"
#include "../events/NotificationEvent.h"
#include "../Point.h"

using json = nlohmann::json;

// Matrix Transformation
void to_json(json &j, const Matrix &m);
void from_json(const json &j, Matrix &m);

// Picturable Transformation
void to_json(json &j, const Picturable &p);
void from_json(const json &j, Picturable &p);

// Point Transformation
void to_json(json &j, const Point &p);
void from_json(const json &j, Point &p);

// NotificationEvent Transformation
void to_json(json &j, const NotificationEvent &e);
void from_json(const json &j, NotificationEvent &e);

// ClientEvent Transformation
void to_json(json &j, const ClientEvent &e);
void from_json(const json &j, ClientEvent &e);

// GameStatusEvent Transformation
void to_json(json &j, const GameStatusEvent &e);
void from_json(const json &j, GameStatusEvent &e);

// MapConfigurationEvent Transformation
void to_json(json &j, const MapConfigurationEvent &m);
void from_json(const json &j, MapConfigurationEvent &m);

#endif //__JSON__CONVERSION_H__
