#pragma once
#include "Singletons.h"
class BaseCollision
{
protected:
	int gID;
	SDL_Rect col;
	SDL_Rect paint;
public:
	void init();
	void update();
	void render();
	SDL_Rect* getCol();
};

