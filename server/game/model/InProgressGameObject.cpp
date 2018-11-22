#include "InProgressGameObject.h"

#include "Player.h"

InProgressGameObject::InProgressGameObject(SelectableGameObject* selectableGameObject)
: GameObject(*(GameObject*)selectableGameObject), selectableGameObject(selectableGameObject) {}

#define TICKS_PER_PORCENTAGE_RAISE (TICKS_UNTIL_COMPLETED / 100)

void InProgressGameObject::tick() {
    if (porcentage >= 100) return;
    if (GameObject::checkCounter(counter, TICKS_PER_PORCENTAGE_RAISE)) {
        haveIChanged = true;
        porcentage++;
    }
}

Picturable InProgressGameObject::getState() const {
    return {player.id, id, sprite, false, {0, 0}, {0, 0}, 0, 0, porcentage};
}

bool InProgressGameObject::completed() const {
    return porcentage >= 100;
}

SelectableGameObject* InProgressGameObject::getObject() const {
    return selectableGameObject;
}

unsigned int InProgressGameObject::getId() const {
    return id;
}
