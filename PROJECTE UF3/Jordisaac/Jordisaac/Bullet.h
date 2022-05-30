#pragma once
#include "BaseCollision.h"
#include "enums.h"
#include <vector>
class Bullet :
    public BaseCollision
{
private:
    float velocity;
    float damage;
    BULLET_DIRECTION dir;
    int type;
    Rect initPos;
    int maxMove;
    bool destroy;
    std::vector<int> sID;
public:
    Bullet(float vel, int t, float range, float dmg, Rect* sp, LOOKING coord, DIAGONALS diagonals = NONE);
    ~Bullet();
    int getType() { return type; };
    float getDamage() { return damage; };
    bool mustDestroy() { return destroy; };
    void update();
    void render();
    void load();
};

