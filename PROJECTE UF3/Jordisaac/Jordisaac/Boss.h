#pragma once
#include "Enemy.h"
class Boss :
    public Enemy
{
public:
    Boss();
    ~Boss();
    //virtual void setAngle(int a);
    virtual void init();
    virtual void update();
    virtual void render();
};

