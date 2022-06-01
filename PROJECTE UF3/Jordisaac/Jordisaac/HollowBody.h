#pragma once
#include "Boss.h"
class HollowBody :
    public Boss
{
    bool head;
    int angle;
    Rect rebotes;
    LOOKING orientacio;
    bool inited;
    bool touched;
public:
    HollowBody(bool h = false);
    ~HollowBody();
    void setAngle(int a) { angle = a; };
    void init();
    void update();
    void render();
    bool hasTouched() { return touched; };
    bool isInited() { return inited; };
};

