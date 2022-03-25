#pragma once
#include "Boss.h"
class Hollow :
    public Boss
{
    int gBody;
public:
    Hollow();
    ~Hollow();
    void init();
    void update();
    void render();
};

