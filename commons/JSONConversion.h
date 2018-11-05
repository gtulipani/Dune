#ifndef __JSON__CONVERSION_H__
#define __JSON__CONVERSION_H__

#include <iostream>
#include "json.hpp"
#include "Event.h"
#include "MapConfigurationEvent.h"
#include "Point.h"

using json = nlohmann::json;

// Event Transformation
void to_json(json &j, const Event &e) {
    j = json{
            {"id",   e.id},
            {"type", e.type},
            {"dst",  e.dst}
    };
    std::cout << j << std::endl;
}
void from_json(const json &j, Event &e) {
    std::cout << j << std::endl;
    j.at("id").get_to(e.id);
    j.at("type").get_to(e.type);
    j.at("dst").get_to(e.dst);
}

// Matrix Transformation
void to_json(json &j, const Matrix &m) {
    j = json{
            {"vec", m.vec},
            {"rows_quantity", m.rows_quantity},
            {"columns_quantity",   m.columns_quantity}
    };
    std::cout << j << std::endl;
}
void from_json(const json &j, Matrix &m) {
    std::cout << j << std::endl;
    j.at("vec").get_to(m.vec);
    j.at("rows_quantity").get_to(m.rows_quantity);
    j.at("columns_quantity").get_to(m.columns_quantity);
}

// MapConfigurationEvent Transformation
void to_json(json &j, const MapConfigurationEvent &m) {
    j = json{
            {"matrix",   m.matrix}
    };
    std::cout << j << std::endl;
}
void from_json(const json &j, MapConfigurationEvent &m) {
    std::cout << j << std::endl;
    j.at("matrix").get_to(m.matrix);
}

// Point Transformation
void to_json(json &j, const Point &p) {
    j = json{
            {"row",    p.row},
            {"column", p.col}
    };
}
void from_json(const json &j, Point &p) {
    j.at("row").get_to(p.row);
    j.at("column").get_to(p.col);
}


#endif //__JSON__CONVERSION_H__
