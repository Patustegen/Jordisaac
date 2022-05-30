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

	float deltaMove = iVideo->getDeltaTime() / 17.0f;
	float moveX = 0.0f;
	float moveY = 0.0f;
	if (col.x + (col.w / 2) < pPos->getCol()->x + (pPos->getCol()->w / 2))
	{
		moveX = deltaMove;
	}
	else if (col.x + (col.w / 2) > pPos->getCol()->x + (pPos->getCol()->w / 2))
	{
		moveX = -deltaMove;
	}
	if (col.y + (col.h / 2) < pPos->getCol()->y + (pPos->getCol()->h / 2))
	{
		moveY = deltaMove;
	}
	else if (col.y + (col.h / 2) > pPos->getCol()->y + (pPos->getCol()->h / 2))
	{
		moveY = -deltaMove;
	}

	if (moveX != 0.0f && moveY != 0.0f)
	{
		moveX *= 0.7f;
		moveY *= 0.7f;
	}

	float realX;
	float realY;
	float decimX = std::modf(moveX, &realX);
	float decimY = std::modf(moveY, &realY);
	if (col.restX + decimX >= 1)
	{
		realX += 1;
	}
	else if (col.restX + decimX <= -1)
	{
		realX -= 1;
	}
	col.x += (int)realX;

	if (!iRoomM->getActualRoom()->roomWalkable(&col) || !iRoomM->getActualRoom()->colWalkable(&col))
	{
		col.x -= (int)realX;
	}
	else
	{
		if (col.x + (col.w / 2) < pPos->getCol()->x + (pPos->getCol()->w / 2))
		{
			if (col.restX + decimX >= 1)
			{
				col.restX -= 1;
			}
			else if (col.restX + decimX <= -1)
			{
				col.restX += 1;
			}
			col.restX += decimX;
		}
		else if (col.x + (col.w / 2) > pPos->getCol()->x + (pPos->getCol()->w / 2))
		{
			if (col.restX + decimX >= 1)
			{
				col.restX -= 1;
			}
			else if (col.restX + decimX <= -1)
			{
				col.restX += 1;
			}
			col.restX += decimX;
		}
	}

	if (col.restY + decimY >= 1)
	{
		realY += 1;
	}
	else if (col.restY + decimY <= -1)
	{
		realY -= 1;
	}
	col.y += (int)realY;

	if (!iRoomM->getActualRoom()->roomWalkable(&col) || !iRoomM->getActualRoom()->colWalkable(&col))
	{
		col.y -= (int)realY;
	}
	else 
	{
		if (col.y + (col.h / 2) < pPos->getCol()->y + (pPos->getCol()->h / 2))
		{
			if (col.restY + decimY >= 1)
			{
				col.restY -= 1;
			}
			else if (col.restY + decimY <= -1)
			{
				col.restY += 1;
			}
			col.restY += decimY;
		}
		else if (col.y + (col.h / 2) > pPos->getCol()->y + (pPos->getCol()->h / 2))
		{
			if (col.restY + decimY >= 1)
			{
				col.restY -= 1;
			}
			else if (col.restY + decimY <= -1)
			{
				col.restY += 1;
			}
			col.restY += decimY;
		}
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
	hp = 3;
	load();
}

AttackFly::~AttackFly()
{
}
