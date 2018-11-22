#ifndef __IN_PROGRESS_GAME_OBJECT_H__
#define __IN_PROGRESS_GAME_OBJECT_H__

#define TICKS_UNTIL_COMPLETED 2000U // 10s

#include "GameObject.h"

class SelectableGameObject;

class InProgressGameObject : public GameObject {
    private:
    int porcentage = 0;
    unsigned int counter = 0;
    SelectableGameObject* selectableGameObject;

    public:
    explicit InProgressGameObject(SelectableGameObject* gameObject);

    virtual void tick() override;

    virtual Picturable getState() const override;

    bool completed() const;

    unsigned int getId() const;

    SelectableGameObject* getObject() const;

    virtual ~InProgressGameObject() = default;
};

#endif
