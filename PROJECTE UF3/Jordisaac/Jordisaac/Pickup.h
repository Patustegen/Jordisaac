#pragma once
#include "BaseCollision.h"
class Pickup :
    public BaseCollision
{
    int type;
    int room;
public:
    void render();
    int getType() { return type; };
    int getRoom() { return room; };
    Pickup(int x, int y, int t);
    ~Pickup();
};

