#pragma once
#include "Enemy.h"
class Boss :
    public Enemy
{
    Boss* pInstance;
public:
    Boss();
    ~Boss();
    Boss* getBoss() { return pInstance;  }
    virtual void init();
    virtual void update();
    virtual void render();
};

