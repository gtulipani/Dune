#ifndef __IN_PROGRESS_GAME_OBJECT_H__
#define __IN_PROGRESS_GAME_OBJECT_H__

#include "GameObject.h"

class SelectableGameObject;

class InProgressGameObject : public GameObject {
    private:
    int porcentage = 0;
    unsigned int counter = 0;
    SelectableGameObject* selectableGameObject;
    const unsigned int ticksUntilCompleted;

    public:
    explicit InProgressGameObject(SelectableGameObject* gameObject, unsigned int time_minutes);

    virtual void tick() override;

    virtual Picturable getState() const override;

    bool completed() const;

    unsigned int getId() const;

    SelectableGameObject* getObject() const;

    virtual ~InProgressGameObject() = default;
};

#endif
