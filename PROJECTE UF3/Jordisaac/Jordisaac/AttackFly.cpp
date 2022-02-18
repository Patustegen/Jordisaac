#include "AttackFly.h"
#include "Singletons.h"

void AttackFly::init()
{

}

void AttackFly::update()
{
	frame += iVideo->getDeltaTime();
	if (frame >= 400)
	{
		frame = 0;
	}


	paint.x = col.x - 10;
	paint.y= col.y - 14;
}

void AttackFly::render()
{
	iVideo->renderGraphic(gID, paint.x, paint.y, paint.w, paint.h, (frame / 100) * paint.w, 0, 2.0f, 2.0f);
}

void AttackFly::load()
{
	gID = iResourceM->loadAndGetGraphicID("Assets\\Enemies\\AttackFly.png");
}

AttackFly::AttackFly(int x, int y)
{
	pPos = nullptr;
	state = IDLE;
	frame = 0;
	col = { x, y, 16, 16 };
	paint = { col.x - 10, col.y - 14, 19, 15 };
	load();
}

AttackFly::~AttackFly()
{
}
