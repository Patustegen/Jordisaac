#pragma once
#include "BaseCharacter.h"
#include "enums.h"
#include "Bullet.h"
#include "Pill.h"
#define MAX_HEARTS 24
#define MAX_PICKUP 99
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

    //Pickups principals
    Pill cons;

    //Pickups secundaris
    int pickups[3];

    int score;

    float stats[STAT_LENGHT];
    bool shooting;
    int cooldown;
    bool eHeart;
    std::vector<HEARTS> sHearts;
    int totalHearts;

    //ASSETS
    int pHead;
    int pMisc;
public:
    void render();
    void update();
    void init();
    int getPickup(int p) { return pickups[p]; };
    bool PickupUp(int p, int q = 1);
    float getStat(int nStat) { return stats[nStat]; };
    STATE getState() { return state; };
    std::vector<HEARTS> getSHearts() { return sHearts; };
    bool hasEHeart() { return eHeart; };
    bool pickupHeart(HEARTS t);
    bool getHurt();
    Pill* getCons() { return &cons; };
    int getScore() { return score; };
    Player();
    ~Player();
};

