#pragma once
#include "BaseCollision.h"
class Bomb :
    public BaseCollision
{
    bool exploded;
    int timer;
public:
    void update();
    void render();
    bool hasExploded() { return exploded; };
    Bomb(int x, int y);
    ~Bomb();
};

