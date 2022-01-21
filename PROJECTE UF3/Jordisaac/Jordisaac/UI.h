#pragma once
#include "Singletons.h"
#include "Player.h"
#define MARGIN 30
#define H_W 28
#define H_H 26

enum HEART_TYPES
{
	RED_H, SOUL_H, BLACK_H, ETERNAL_H
};

class UI
{
private:
	SDL_Rect rHearts;
	Player* mPlayer;
	int gHeart;
public:
	UI();
	~UI();
	void setPlayer(Player* nP) { mPlayer = nP; };
	void load();
	void init();
	void update();
	void render();
};

