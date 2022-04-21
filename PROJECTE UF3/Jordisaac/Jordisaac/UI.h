#pragma once
#include "Singletons.h"
#include "Player.h"
#define MARGIN 30
#define H_W 28
#define H_H 26
#define PU_W 33
#define PU_H 45

enum HEART_TYPES
{
	RED_H, SOUL_H, BLACK_H, ETERNAL_H
};

class UI
{
private:
	Rect rHearts;
	Rect rPickups;
	Player* mPlayer;
	int gHeart;
	int gPickups;
public:
	UI();
	~UI();
	void setPlayer(Player* nP) { mPlayer = nP; };
	void load();
	void init();
	void update();
	void render();
};

