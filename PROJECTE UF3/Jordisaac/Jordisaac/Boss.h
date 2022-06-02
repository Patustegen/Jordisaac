#pragma once
#include "Enemy.h"
class Boss :
    public Enemy
{
    int bossMusic;
public:
    Boss();
    ~Boss();
    virtual void init();
    virtual void update();
    virtual void render();
};

