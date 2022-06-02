#pragma once
#include "BaseCharacter.h"
#include "Player.h"
class Enemy :
    public BaseCharacter
{
protected:
    Player* pPos;
    int points;
public:
    virtual void init();
    virtual void update();
    virtual void render();
    int getPoints() { return points; };
    void setPlayer(Player* nPlayer) { pPos = nPlayer; };
    Enemy();
    ~Enemy();
};

