#pragma once
#include "Enemy.h"
class AttackFly :
    public Enemy
{
    STATE state;
public:
    void init();
    void update();
    void render();
    void load();
    AttackFly(int x, int y);
    ~AttackFly();
};

