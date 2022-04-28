#pragma once
#include "BaseCollision.h"

enum BOMB_ESTATS { COUNTDOWN, EXPLODING, EXPLODED };

class Bomb :
    public BaseCollision
{
    bool destroy;
    BOMB_ESTATS estats;
    int timer;
public:
    void update();
    void render();
    bool mustDestroy() { return destroy; };
    Bomb(int x, int y);
    ~Bomb();
};

