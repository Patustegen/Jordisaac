#include "Pooter.h"
#include "Singletons.h"

void Pooter::init()
{
}

void Pooter::update()
{
}

void Pooter::render()
{
	iVideo->renderGraphic(gID, paint.x, paint.y, paint.w, paint.h, (frame / 100) * paint.w, state * paint.h, 2.0f, 2.0f);
}

void Pooter::load()
{
	gID = iResourceM->loadAndGetGraphicID("Assets\\Enemies\\Pooter.png");
}

Pooter::Pooter(int x, int y)
{
	pPos = nullptr;
	state = MOVING_RIGHT;
	frame = 0;
	col = { x, y, 25, 20 };
	paint = { col.x - 12, col.y - 15, 24, 25 };
	hp = 6;
}

Pooter::~Pooter()
{
}
