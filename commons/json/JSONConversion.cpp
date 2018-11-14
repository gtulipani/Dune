#include "JSONConversion.h"

// Matrix Transformation
void to_json(json &j, const Matrix &m) {
    j = json{
            {"vec",              m.vec},
            {"rows_quantity",    m.rows_quantity},
            {"columns_quantity", m.columns_quantity}
    };
}

void from_json(const json &j, Matrix &m) {
    j.at("vec").get_to(m.vec);
    j.at("rows_quantity").get_to(m.rows_quantity);
    j.at("columns_quantity").get_to(m.columns_quantity);
}

// Picturable Transformation
void to_json(json &j, const Picturable &p) {
    j = json{
            {"id",       p.id},
            {"sprite",   p.sprite},
            {"selected", p.selected},
            {"position", p.position},
            {"health",     p.health},
    };
}

void from_json(const json &j, Picturable &p) {
    j.at("id").get_to(p.id);
    j.at("sprite").get_to(p.sprite);
    j.at("selected").get_to(p.selected);
    j.at("position").get_to(p.position);
    j.at("health").get_to(p.health);
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

// NotificationEvent Transformation
void to_json(json &j, const NotificationEvent &e) {
    j = json{
            {"message",   e.message}
    };
}

void from_json(const json &j, NotificationEvent &p) {
    j.at("message").get_to(p.message);
}

// ClientEvent Transformation
void to_json(json &j, const ClientEvent &e) {
    j = json{
            {"player_id",   e.player_id},
            {"type", e.type},
            {"position",  e.position}
    };
}

void from_json(const json &j, ClientEvent &e) {
    j.at("player_id").get_to(e.player_id);
    j.at("type").get_to(e.type);
    j.at("position").get_to(e.position);
}

// GameStatusEvent Transformation
void to_json(json &j, const GameStatusEvent &e) {
    j = json{
            {"picturables", e.picturables}
    };
}

void from_json(const json &j, GameStatusEvent &e) {
    j.at("picturables").get_to(e.picturables);
}

// MapConfigurationEvent Transformation
void to_json(json &j, const MapConfigurationEvent &m) {
    j = json{
            {"matrix", m.matrix}
    };
}

void from_json(const json &j, MapConfigurationEvent &m) {
    j.at("matrix").get_to(m.matrix);
}
