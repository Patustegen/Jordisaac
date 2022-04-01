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
    Rect initPos;
    int maxMove;
    bool destroy;
public:
    Bullet(float vel, int t, float range, Rect* sp, LOOKING coord, DIAGONALS diagonals = NONE);
    int getType() { return type; };
    bool mustDestroy() { return destroy; };
    void update();
    void render();
    void load();
};

