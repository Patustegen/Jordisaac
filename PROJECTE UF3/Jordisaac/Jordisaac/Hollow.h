#pragma once
#include "Boss.h"
class Hollow :
    public Boss
{
    bool head;
    int angle;
    Rect rebotes;
    LOOKING orientacio;
public:
    Hollow(bool h = false);
    ~Hollow();
    void setAngle(int a) { angle = a; };
    void init();
    void update();
    void render();
};

