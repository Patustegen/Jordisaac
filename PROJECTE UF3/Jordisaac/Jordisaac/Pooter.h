#pragma once
#include "Enemy.h"
enum STATE_POOTER { MOVING_RIGHT, MOVING_LEFT, SHOOTING_RIGHT, SHOOTING_LEFT };

class Pooter :
    public Enemy
{
    STATE_POOTER state;
public:
    void init();
    void update();
    void render();
    void load();
    Pooter(int x, int y);
    ~Pooter();
};

