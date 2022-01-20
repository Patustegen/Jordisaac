#pragma once
#include "Singletons.h"
#define MARGIN 30
#define H_W 28
#define H_H 26

class UI
{
private:
	SDL_Rect rHearts;
	int gHeart;
public:
	void load();
	void init();
	void update();
	void render();
};

