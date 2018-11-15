#ifndef __JSON_CONVERSION_H__
#define __JSON_CONVERSION_H__

#include <json/json.hpp>
#include <json/JSONConversion.h>
#include "../model/Map.h"

// Map Transformation
void to_json(json &j, const Map &m);

void from_json(const json &j, Map &m);

#endif
