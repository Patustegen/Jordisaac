#pragma once
#include "BaseCharacter.h"
#include "enums.h"

enum STATS
{
    DAMAGE, TEARS, RANGE, SHOT_SPEED, SPEED, LUCK,
    STAT_LENGHT
};

class Player :
    public BaseCharacter
{
private:
    STATE state;
    STATE hstate;
    LOOKING lHead;
    LOOKING lBody;
    DIAGONALS mDiagonals;
    SDL_Rect Head;

    float stats[STAT_LENGHT];
    bool shooting;
    int cooldown;
    int frame;

    //ASSETS
    int pHead;
    int pMisc;
    int gFrame;
public:
    void render();
    void update();
    Player();
    ~Player();
};

