#include "AttackFly.h"

void AttackFly::init()
{

}

void AttackFly::update()
{
	if (pPos->x - col.x < pPos->y - col.y)
	{

	}
	else
	{

	}
}

void AttackFly::render()
{
}

AttackFly::AttackFly(int x, int y)
{
	pPos = nullptr;
	state = IDLE;
	col = { x,y,10,10 };
}

AttackFly::~AttackFly()
{
}
