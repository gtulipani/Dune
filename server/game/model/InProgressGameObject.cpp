#include "InProgressGameObject.h"

#include "Player.h"
#include <Tick.h>

InProgressGameObject::InProgressGameObject(SelectableGameObject* selectableGameObject, int time_minutes)
: GameObject(*(GameObject*)selectableGameObject), selectableGameObject(selectableGameObject), ticksUntilCompleted(time_minutes * 60 * TICKS_PER_SECOND) {}

void InProgressGameObject::tick() {
    if (porcentage >= 100) return;
    if (GameObject::checkCounter(counter, ticksUntilCompleted / 100)) {
        haveIChanged = true;
        porcentage++;
    }
}

Picturable InProgressGameObject::getState() const {
    return {player.id, id, name, DEFAULT_SPRITE_DIRECTION, DEFAULT_SPRITE_MOTION, false, {0, 0}, {0, 0}, 0, 0, porcentage};
}

bool InProgressGameObject::completed() const {
    return porcentage >= 100;
}

SelectableGameObject* InProgressGameObject::getObject() const {
    return selectableGameObject;
}

int InProgressGameObject::getId() const {
    return id;
}
