#ifndef __JSON_UTILS__
#define __JSON_UTILS__

#include <string>
#include "json.hpp"
#include "../events/ClientEvent.h"
#include "../Point.h"

using namespace std;
using json = nlohmann::json;

namespace json_utils {
    json parseAsJson(const string &game_units_parameters_path);
}

#endif //__JSON_UTILS__
