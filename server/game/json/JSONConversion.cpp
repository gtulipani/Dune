#include "JSONConversion.h"

// Map Transformation
void to_json(json &j, const Map &m) {
    j = json{
        {"construction_center_positions",   m.constructionCenterPositions},
        {"especia_positions",               m.especia_positions},
        {"matrix",                          m.mat}
    };
}

void from_json(const json &j, Map &m) {
    j.at("construction_center_positions").get_to(m.constructionCenterPositions);
    j.at("especia_positions").get_to(m.especia_positions);
    j.at("matrix").get_to(m.mat);
}
