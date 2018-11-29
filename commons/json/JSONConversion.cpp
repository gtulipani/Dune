#include <iostream>
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
            {"player_id",           p.player_id},
            {"id",                  p.id},
            {"type",                p.type},
            {"sprite_direction",    p.sprite_direction},
            {"sprite_motion",       p.sprite_motion},
            {"selected",            p.selected},
            {"position",            p.position},
            {"size",                p.size},
            {"health",              p.health},
            {"max_health",          p.max_health},
            {"porcentage",          p.porcentage}
    };
    std::cout << j << std::endl;
}

void from_json(const json &j, Picturable &p) {
    std::cout << j << std::endl;
    j.at("player_id").get_to(p.player_id);
    j.at("id").get_to(p.id);
    j.at("type").get_to(p.type);
    j.at("sprite_direction").get_to(p.sprite_direction);
    j.at("sprite_motion").get_to(p.sprite_motion);
    j.at("selected").get_to(p.selected);
    j.at("position").get_to(p.position);
    j.at("size").get_to(p.size);
    j.at("health").get_to(p.health);
    j.at("max_health").get_to(p.max_health);
    j.at("porcentage").get_to(p.porcentage);
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
            {"picturable_id", e.picturable_id},
            {"click_position",  e.click_position},
            {"release_position",  e.release_position}
    };
    std::cout << j << std::endl;
}

void from_json(const json &j, ClientEvent &e) {
    std::cout << j << std::endl;
    j.at("player_id").get_to(e.player_id);
    j.at("type").get_to(e.type);
    j.at("picturable_id").get_to(e.picturable_id);
    j.at("click_position").get_to(e.click_position);
    j.at("release_position").get_to(e.release_position);
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

// GameConfigurationEvent Transformation
void to_json(json &j, const GameConfigurationEvent &g) {
    j = json{
            {"player_id", g.player_id},
            {"matrix", g.matrix}
    };
}

void from_json(const json &j, GameConfigurationEvent &g) {
    j.at("player_id").get_to(g.player_id);
    j.at("matrix").get_to(g.matrix);
}
