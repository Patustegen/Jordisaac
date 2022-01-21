#include "UI.h"

UI::UI()
{
	rHearts = { 0,0,0,0 };
	gHeart = -1;
	mPlayer = nullptr;
}

UI::~UI()
{
}

void UI::load()
{
	gHeart = iResourceM->loadAndGetGraphicID("Assets\\UI\\UIHearts.png");
}

void UI::init()
{
	rHearts = { MARGIN, MARGIN, H_W, H_H };
}

void UI::render()
{
	rHearts.x = MARGIN;
	rHearts.y = MARGIN;
	int nHearts = mPlayer->getStat(LIFE_CAPACITY) / 2;
	float life = mPlayer->getHP();
	for (int i = 0; i < nHearts; i++)
	{
		if (life > 1)
		{
			iVideo->renderGraphic(gHeart, rHearts.x, rHearts.y, rHearts.w, rHearts.h, 0, 0, 1.5, 1.5);
		}
		else if (life == 1)
		{
			iVideo->renderGraphic(gHeart, rHearts.x, rHearts.y, rHearts.w, rHearts.h, rHearts.w, 0, 1.5, 1.5);
		}
		else
		{
			iVideo->renderGraphic(gHeart, rHearts.x, rHearts.y, rHearts.w, rHearts.h, rHearts.w * 1.5);
		}
		life -= 2;
		if (i == 5)
		{
			rHearts.y += rHearts.h * 1.5 - 10;
			rHearts.x = MARGIN;
		}
		else
		{
			rHearts.x += rHearts.w * 1.5 - 10;
		}
	}
}
