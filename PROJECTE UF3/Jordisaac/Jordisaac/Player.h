#pragma once
#include "BaseCharacter.h"

enum STATE {IDLE, MOVING, HURT, DEATH, USING};
enum LOOKING {UP, RIGHT, DOWN, LEFT};

class Player :
    public BaseCharacter
{
private:
    STATE state;
    LOOKING looking;
public:
};

