#include "Bomb.h"
#include "Singletons.h"

void Bomb::update()
{
	switch (estats)
	{
	case COUNTDOWN:
		timer -= iVideo->getDeltaTime();
		if (timer <= 0)
		{
			estats = EXPLODING;
			timer = 500;
			col.x -= col.w / 2;
			col.y -= col.h / 2;
			col.w *= 2;
			col.h *= 2;
			paint.x = col.x;
			paint.y = col.y;
		}
		break;
	case EXPLODING:
		estats = EXPLODED;
		break;
	case EXPLODED:
		timer -= iVideo->getDeltaTime();
		if (timer <= 0) destroy = true;
		break;
	default:
		break;
	}
}

void Bomb::render()
{
	if (estats == COUNTDOWN) iVideo->renderGraphic(gID, paint.x, paint.y, paint.w, paint.h, 0, 0, 2.0f, 2.0f);
	else iVideo->renderGraphic(gID, paint.x, paint.y, paint.w, paint.h, 0, 0, 4.0f, 4.0f);
}

Bomb::Bomb(int x, int y)
{
	estats = COUNTDOWN;
	destroy = false;
	timer = 3000;
	paint = { x - 10, y - 10, 20, 21 };
	col = { x - 20, y - 21, 40, 42 };
	gID = iResourceM->loadAndGetGraphicID("Assets/pickups/bomb.png");
}

Bomb::~Bomb()
{
}
