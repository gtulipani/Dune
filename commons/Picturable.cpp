#include "Picturable.h"

Picturable::Picturable(int player_id, int id, std::string name, int sprite_direction, int sprite_motion, bool selected, Point position, Point size, int health, int max_health, int porcentage) :
    player_id(player_id),
    id(id),
    name(std::move(name)),
    sprite_direction(sprite_direction),
    sprite_motion(sprite_motion),
    selected(selected),
    position(std::move(position)),
    size(std::move(size)),
    health(health),
    max_health(max_health),
    porcentage(porcentage) {}

Picturable::Picturable(const Picturable &other) : Picturable(
        other.player_id,
        other.id,
        other.name,
        other.sprite_direction,
        other.sprite_motion,
        other.selected,
        other.position,
        other.size,
        other.health,
        other.max_health,
        other.porcentage) {}

Picturable::Picturable(Picturable &&other) noexcept : Picturable(
        other.player_id,
        other.id,
        other.name,
        other.sprite_direction,
        other.sprite_motion,
        other.selected,
        std::move(other.position),
        std::move(other.size),
        other.health,
        other.max_health,
        other.porcentage) {
    other.player_id = 0;
    other.id = 0;
    other.sprite_direction = 0;
    other.sprite_motion = 0;
    other.selected = false;
    other.health = 0;
    other.max_health = 0;
    other.porcentage = 0;
}

Picturable &Picturable::operator=(const Picturable &other) {
    if (this == &other) {
        return *this; // other is myself!
    }

    // Copy values
    this->player_id = other.player_id;
    this->id = other.id;
    this->name = other.name;
    this->sprite_direction = other.sprite_direction;
    this->sprite_motion = other.sprite_motion;
    this->selected = other.selected;
    this->position = other.position;
    this->size = other.size;
    this->health = other.health;
    this->max_health = other.max_health;
    this->porcentage = other.porcentage;
    return *this;
}

Picturable &Picturable::operator=(Picturable &&other) noexcept {
    if (this == &other) {
        return *this; // other is myself!
    }

    // Copy values
    this->player_id = other.player_id;
    this->id = other.id;
    this->name =std::move(other.name);
    this->sprite_direction = other.sprite_direction;
    this->sprite_motion = other.sprite_motion;
    this->selected = other.selected;
    this->position = other.position;
    this->size = other.size;
    this->health = other.health;
    this->max_health = other.max_health;
    this->porcentage = other.porcentage;

    other.player_id = 0;
    other.id = 0;
    other.sprite_direction = 0;
    other.sprite_motion = 0;
    other.selected = false;
    other.health = 0;
    other.max_health = 0;
    other.porcentage = 0;

    return *this;
}
