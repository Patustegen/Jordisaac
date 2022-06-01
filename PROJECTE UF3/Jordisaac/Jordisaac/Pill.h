#pragma once
#include "BaseCollision.h"
class Pill :
    public BaseCollision
{
    int type;
    int sprite;
    int sID[3];
public:
    int getType() { return sprite; };
    void setPill(int t, int s);
    void render();
    void Use();
    Pill();
    ~Pill();
};

