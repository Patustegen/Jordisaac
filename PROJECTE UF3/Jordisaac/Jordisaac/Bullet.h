#pragma once
#include "BaseCollision.h"
#include "enums.h"
class Bullet :
    public BaseCollision
{
private:
    float velocity;
    BULLET_DIRECTION dir;
    int type;
    int time;
public:
    Bullet(float vel, int t, Rect* sp, LOOKING coord, DIAGONALS diagonals = NONE);
    int getType() { return type; };
    void update();
    void render();
    void load();
};

