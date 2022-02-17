#pragma once
#include "BaseCharacter.h"
#include "enums.h"
class Enemy :
    public BaseCharacter
{
protected:
    static Rect* pPos;
    Rect col;
public:
    virtual void init();
    virtual void update();
    virtual void render();
    static void setPPos(Rect* nPos) { pPos = nPos; };
    Enemy();
    ~Enemy();
};

