#pragma once
#include "Boss.h"
#include "HollowBody.h"
#include "vector"
class Hollow :
    public Boss
{
    std::vector<HollowBody*> mHBody;
    std::vector<HollowBody*> movBody;
public:
    void init();
    void update();
    void render();
    std::vector<HollowBody*> getHBody() { return mHBody; };
    Hollow();
    ~Hollow();
};

