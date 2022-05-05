#pragma once
#include "BaseCharacter.h"
#include "enums.h"
#include "Bullet.h"

enum STATS
{
    DAMAGE, TEARS, RANGE, SHOT_SPEED, SPEED, LUCK, LIFE_CAPACITY,
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
    Rect Head;
    Rect Misc;

    //Pickups secundaris
    int pickups[3];


    float stats[STAT_LENGHT];
    bool shooting;
    int cooldown;

    //ASSETS
    int pHead;
    int pMisc;
    int gFrame;
public:
    void render();
    void update();
    void init();
    int getPickup(int p) { return pickups[p]; };
    void PickupUp(int p, int q = 1) { pickups[p] += q; };
    float getStat(int nStat) { return stats[nStat]; };
    bool getHurt();
    Player();
    ~Player();
};

