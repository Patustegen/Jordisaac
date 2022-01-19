#pragma once
#include "BaseCharacter.h"
#include "enums.h"

class Player :
    public BaseCharacter
{
private:
    STATE state;
    STATE hstate;
    LOOKING lHead;
    LOOKING lBody;
    SDL_Rect Head;
    int pHead;
    int pMisc;
    int frame;
    int gFrame;
    int cooldown;
    bool shooting;
public:
    void render();
    void update();
    Player();
    ~Player();
};

