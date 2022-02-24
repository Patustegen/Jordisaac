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
