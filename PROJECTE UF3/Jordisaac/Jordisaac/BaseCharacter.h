#pragma once
#include "BaseCollision.h"
#include <vector>
class BaseCharacter :
    public BaseCollision
{
protected:
    float hp;
    std::vector<int> sID;
    int frame;
public:
    float getHP() { return hp; };
    void hurt(float h = 1);
};

