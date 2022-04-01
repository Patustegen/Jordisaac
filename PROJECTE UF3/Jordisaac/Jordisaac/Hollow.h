#pragma once
#include "Boss.h"
#include "enums.h"
class Hollow :
    public Boss
{
    int gBody;
    int angle;
    LOOKING orientacio;
public:
    Hollow();
    ~Hollow();
    void init();
    void update();
    void render();
};

