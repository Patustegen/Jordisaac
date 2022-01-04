#pragma once
#include "BaseCollision.h"
class BaseCharacter :
    public BaseCollision
{
protected:
    int hp;
    std::vector<int> sID;
public:
    int getHP() { return hp; };
};

