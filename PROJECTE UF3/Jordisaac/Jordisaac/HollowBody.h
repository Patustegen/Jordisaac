#pragma once
#include "Boss.h"
class HollowBody :
    public Boss
{
    bool head;
    int angle;
    Rect rebotes;
    LOOKING orientacio;
public:
    HollowBody(bool h = false);
    ~HollowBody();
    void setAngle(int a) { angle = a; };
    void init();
    void update();
    void render();
};

