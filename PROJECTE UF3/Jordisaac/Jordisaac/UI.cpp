#include "UI.h"

UI::UI()
{
	rHearts = { 0,0,0,0 };
	rPickups = { 0,0,0,0 };
	rNumbers = { 0,0,0,0 };
	gHeart = -1;
	gPickups = -1;
	gNumbers = -1;
	mPlayer = nullptr;
}

UI::~UI()
{
}

void UI::load()
{
	gHeart = iResourceM->loadAndGetGraphicID("Assets/UI/UIHearts.png");
	gPickups = iResourceM->loadAndGetGraphicID("Assets/UI/UIPickups.png");
	gNumbers = iResourceM->loadAndGetGraphicID("Assets/UI/UINumbers.png");
}

void UI::init()
{
	rHearts = { MARGIN * 4, MARGIN, H_W, H_H };
	rPickups = { MARGIN, MARGIN * 3, PU_W, PU_H };
	rNumbers = { MARGIN + rPickups.w, MARGIN * 3, N_W, N_H };
}

void UI::render()
{
	rPickups.y = MARGIN * 3;
	for (int i = 0; i < 3; i++)
	{
		iVideo->renderGraphic(gPickups, rPickups.x, rPickups.y, rPickups.w, rPickups.h, 0, rPickups.h * i, 0.75f, 0.75f);
		rNumbers.x = (int)(rPickups.x + rPickups.w * 0.75f);
		rNumbers.y = rPickups.y + 8;
		int result = mPlayer->getPickup(i) / 10;
		iVideo->renderGraphic(gNumbers, rNumbers.x, rNumbers.y, rNumbers.w, rNumbers.h, rNumbers.w * (mPlayer->getPickup(i) / 10), 0, 2.0f, 2.0f);
		rNumbers.x += rNumbers.w * 2;
		result = mPlayer->getPickup(i) % 10;
		iVideo->renderGraphic(gNumbers, rNumbers.x, rNumbers.y, rNumbers.w, rNumbers.h, rNumbers.w * (mPlayer->getPickup(i) % 10), 0, 2.0f, 2.0f);

		rPickups.y += (int)(rPickups.h * 0.75f);
	}
	rHearts.x = MARGIN * 4;
	rHearts.y = MARGIN;
	int nHearts = (int)mPlayer->getStat(LIFE_CAPACITY) / 2;
	float life = (float)mPlayer->getHP();
	for (int i = 0; i < nHearts; i++)
	{
		if (life > 1) iVideo->renderGraphic(gHeart, rHearts.x, rHearts.y, rHearts.w, rHearts.h, 0, 0, 1.5f, 1.5f);
		else if (life == 1) iVideo->renderGraphic(gHeart, rHearts.x, rHearts.y, rHearts.w, rHearts.h, rHearts.w, 0, 1.5f, 1.5f);
		else iVideo->renderGraphic(gHeart, rHearts.x, rHearts.y, rHearts.w, rHearts.h, rHearts.w * 2, 0, 1.5f, 1.5f);
		life -= 2;
		if (i == 5)
		{
			rHearts.y += (int)(rHearts.h * 1.5f - 10);
			rHearts.x = MARGIN * 4;
		}
		else rHearts.x += (int)(rHearts.w * 1.5f - 10);
	}
}
