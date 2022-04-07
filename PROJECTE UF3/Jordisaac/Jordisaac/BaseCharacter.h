#pragma once
#include "BaseCollision.h"
#include <vector>
class BaseCharacter :
    public BaseCollision
{
protected:
    int hp;
    std::vector<int> sID;
    int frame;
public:
    int getHP() { return hp; };
    void hurt(int h = 1);
};

