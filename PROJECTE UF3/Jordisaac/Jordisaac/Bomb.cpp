#include "Bomb.h"
#include "Singletons.h"

void Bomb::update()
{
	timer -= iVideo->getDeltaTime();
	if (timer <= 0) exploded = true;
}

void Bomb::render()
{
}

Bomb::Bomb(int x, int y)
{
	exploded = false;
	timer = 3000;
	col = { x, y };
}

Bomb::~Bomb()
{
}
