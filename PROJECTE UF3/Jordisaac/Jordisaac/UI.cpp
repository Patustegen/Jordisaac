#include "UI.h"

UI::UI()
{
	rHearts = { 0,0,0,0 };
	rPickups = { 0,0,0,0 };
	gHeart = -1;
	gPickups = -1;
	mPlayer = nullptr;
}

UI::~UI()
{
}

void UI::load()
{
	gHeart = iResourceM->loadAndGetGraphicID("Assets/UI/UIHearts.png");
	gPickups = iResourceM->loadAndGetGraphicID("Assets/UI/UIPickups.png");
}

void UI::init()
{
	rHearts = { MARGIN * 2, MARGIN, H_W, H_H };
	rPickups = { MARGIN, MARGIN * 2, PU_W, PU_H };
}

void UI::render()
{
	rPickups.y = MARGIN * 2;
	for (int i = 0; i < 3; i++)
	{
		iVideo->renderGraphic(gPickups, rPickups.x, rPickups.y, rPickups.w, rPickups.h, 0, rPickups.h * i);
		rPickups.y += rPickups.h;
	}
	rHearts.x = MARGIN * 2;
	rHearts.y = MARGIN;
	int nHearts = (int)mPlayer->getStat(LIFE_CAPACITY) / 2;
	float life = (float)mPlayer->getHP();
	for (int i = 0; i < nHearts; i++)
	{
		if (life > 1)
		{
			iVideo->renderGraphic(gHeart, rHearts.x, rHearts.y, rHearts.w, rHearts.h, 0, 0, 1.5f, 1.5f);
		}
		else if (life == 1)
		{
			iVideo->renderGraphic(gHeart, rHearts.x, rHearts.y, rHearts.w, rHearts.h, rHearts.w, 0, 1.5f, 1.5f);
		}
		else
		{
			iVideo->renderGraphic(gHeart, rHearts.x, rHearts.y, rHearts.w, rHearts.h, rHearts.w * 2, 0, 1.5f, 1.5f);
		}
		life -= 2;
		if (i == 5)
		{
			rHearts.y += (int)(rHearts.h * 1.5f - 10);
			rHearts.x = MARGIN;
		}
		else
		{
			rHearts.x += (int)(rHearts.w * 1.5f - 10);
		}
	}
}
