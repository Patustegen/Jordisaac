#pragma once
#include "Utils.h"
class BaseCollision
{
protected:
	int gID;
	Rect col;
	Rect paint;
public:
	void init();
	void update();
	void render();
	Rect* getCol();
};

