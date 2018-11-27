#ifndef __GAME_CONFIGURATION_H__
#define __GAME_CONFIGURATION_H__

class AttackingUnit;
class Cosechadora;

class GameConfiguration {
    public:
    AttackingUnit* getTrike() const;

    Cosechadora* getCosechadora() const;
};

#endif
