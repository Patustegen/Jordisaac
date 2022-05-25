#pragma once
#include "BaseCollision.h"

enum PICKUP_TYPE { NORMAL_PU, CONS_PU, PASSIVE_PU, ACTIVE_PU, TRINKET_PU };

class Pickup :
    public BaseCollision
{
    PICKUP_TYPE type;
    int id;
    int room;
public:
    void render();
    int getId() { return id; };
    PICKUP_TYPE getType() { return type; };
    int getRoom() { return room; };
    Pickup(int x, int y, int i, PICKUP_TYPE t);
    ~Pickup();
};

