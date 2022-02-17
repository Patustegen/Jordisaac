#pragma once
#include "Enemy.h"
class AttackFly :
    public Enemy
{
private:
    STATE state;
    Rect* pPos;
public:
    void init();
    void update();
    void render();
    AttackFly(int x, int y);
    ~AttackFly();
};

