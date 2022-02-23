#pragma once
#include "BaseCharacter.h"
#include "Player.h"
class Enemy :
    public BaseCharacter
{
protected:
    Player* pPos;
public:
    virtual void init();
    virtual void update();
    virtual void render();
    void setPlayer(Player* nPlayer) { pPos = nPlayer; };
    Enemy();
    ~Enemy();
};

