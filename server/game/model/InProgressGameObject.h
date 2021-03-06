#ifndef __IN_PROGRESS_GAME_OBJECT_H__
#define __IN_PROGRESS_GAME_OBJECT_H__

#include "GameObject.h"

class SelectableGameObject;

class InProgressGameObject : public GameObject {
    private:
    int porcentage = 0;
    int counter = 1;
    SelectableGameObject* selectableGameObject;
    const int ticksUntilCompleted;

    public:
    explicit InProgressGameObject(SelectableGameObject* gameObject, int time_minutes);

    virtual void tick() override;

    virtual Picturable getState() const override;

    bool completed() const;

    int getId() const;

    SelectableGameObject* getObject() const;

    virtual ~InProgressGameObject() = default;
};

#endif
