#pragma once
#include "BaseCollision.h"
#include <vector>
class BaseCharacter :
    public BaseCollision
{
protected:
    int hp;
    std::vector<int> sID;
public:
    int getHP() { return hp; };
};

