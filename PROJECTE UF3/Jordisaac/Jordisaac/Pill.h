#pragma once
#include "BaseCollision.h"
class Pill :
    public BaseCollision
{
    int type;
    int sprite;
public:
    void Use();
    Pill(int t, int s);
    ~Pill();
};

