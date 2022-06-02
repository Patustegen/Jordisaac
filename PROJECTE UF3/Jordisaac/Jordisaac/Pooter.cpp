#include "Pooter.h"
#include "Singletons.h"

void Pooter::init()
{
}

void Pooter::update()
{
	frame += iVideo->getDeltaTime();
	cooldown += iVideo->getDeltaTime();
	float deltaMove = iVideo->getDeltaTime() / 17.0f;
	float moveX = 0.0f;
	float moveY = 0.0f;
	float realX = 0.0f;
	float realY = 0.0f;
	float decimX = 0.0f;
	float decimY = 0.0f;
	switch (state)
	{
	case MOVING_RIGHT:
	case MOVING_LEFT:
		if (frame >= 200) frame = 0;
		if (col.x + (col.w / 2) < pPos->getCol()->x + (pPos->getCol()->w / 2))
		{
			moveX = deltaMove;
			state = MOVING_RIGHT;
		}
		else if (col.x + (col.w / 2) > pPos->getCol()->x + (pPos->getCol()->w / 2))
		{
			moveX = -deltaMove;
			state = MOVING_LEFT;
		}
		if (col.y + (col.h / 2) < pPos->getCol()->y + (pPos->getCol()->h / 2))
		{
			moveY = deltaMove;
		}
		else if (col.y + (col.h / 2) > pPos->getCol()->y + (pPos->getCol()->h / 2))
		{
			moveY = -deltaMove;
		}

		if (cooldown > 2000)
		{
			cooldown = 0;
			if (col.x + (col.w / 2) < pPos->getCol()->x + (pPos->getCol()->w / 2))
			{
				state = SHOOTING_RIGHT;
				int angle = atan2((pPos->getCol()->y + pPos->getCol()->h / 2) - (col.y + col.h / 2), (pPos->getCol()->x + pPos->getCol()->w / 2) - (col.x + col.w / 2)) * 180 / PI;
				iBulletM->AddBullet(0.4f, 0, 7.0f, 1.0f, &col, RIGHT, angle);
			}
			else
			{
				state = SHOOTING_LEFT;
				int angle = atan2((pPos->getCol()->y + pPos->getCol()->h / 2) - (col.y + col.h / 2), (pPos->getCol()->x + pPos->getCol()->w / 2) - (col.x + col.w / 2)) * 180 / PI;
				iBulletM->AddBullet(0.4f, 0, 7.0f, 1.0f, &col, LEFT, angle);
			}
		}

		if (moveX != 0.0f && moveY != 0.0f)
		{
			moveX *= 0.4f;
			moveY *= 0.4f;
		}
		decimX = std::modf(moveX, &realX);
		decimY = std::modf(moveY, &realY);

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
		paint.y = col.y - 15;
		break;
	case SHOOTING_RIGHT:
	case SHOOTING_LEFT:
		if (frame >= 500)
		{
			frame = 0;
			state = MOVING_RIGHT;
		}
		break;
	default:
		break;
	}

	
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
	col = { x, y, 25, 24 };
	paint = { col.x - 10, col.y - 15, 24, 25 };
	hp = 6;
	cooldown = 0;
	points = 10;
	load();
}

Pooter::~Pooter()
{
}
