#include "Player.h"
#include "Singletons.h"

void Player::render()
{
	iVideo->renderGraphic(gID, paint.x, paint.y, paint.w, paint.h, (frame / 100) * paint.w, lBody * paint.h,2,2);
	iVideo->renderGraphic(pHead, Head.x, Head.y, Head.w, Head.h, shooting * Head.w, lHead * Head.h,2,2);
	iVideo->renderGraphic(gFrame, col.x, col.y, col.w, col.h);
}

void Player::update()
{
	if (state == DEAD)
	{

	}
	else
	{
		if (cooldown > 0)
		{
			if (cooldown <= 400)
			{
				shooting = false;
			}
			cooldown -= iVideo->getDeltaTime();
		}
		if (iInputM->getEvents(GOUP)) lBody = UP;
		else if (iInputM->getEvents(GODOWN)) lBody = DOWN;
		if (iInputM->getEvents(GORIGHT)) lBody = RIGHT;
		else if (iInputM->getEvents(GOLEFT)) lBody = LEFT;
		if (iInputM->getEvents(SHOOTUP)) lHead = UP;
		if (iInputM->getEvents(SHOOTRIGHT)) lHead = RIGHT;
		if (iInputM->getEvents(SHOOTDOWN)) lHead = DOWN;
		if (iInputM->getEvents(SHOOTLEFT)) lHead = LEFT;
		if (iInputM->getEvents(USEBOMB));
		if (iInputM->getEvents(USEITEM));
		if (iInputM->getEvents(USECONS));
		
		mDiagonals = NONE;

		if (!iInputM->getEvents(GOUP) && !iInputM->getEvents(GORIGHT) && !iInputM->getEvents(GODOWN) && !iInputM->getEvents(GOLEFT)) state = IDLE;
		else if (iInputM->getEvents(GOUP) && !iInputM->getEvents(GORIGHT) && iInputM->getEvents(GODOWN) && !iInputM->getEvents(GOLEFT)) state = IDLE;
		else if (!iInputM->getEvents(GOUP) && iInputM->getEvents(GORIGHT) && !iInputM->getEvents(GODOWN) && iInputM->getEvents(GOLEFT)) state = IDLE;
		else if (iInputM->getEvents(GOUP) && iInputM->getEvents(GORIGHT) && iInputM->getEvents(GODOWN) && !iInputM->getEvents(GOLEFT)) 
		{
			lBody = RIGHT;
			state = MOVING;
		}
		else if (iInputM->getEvents(GOUP) && !iInputM->getEvents(GORIGHT) && iInputM->getEvents(GODOWN) && iInputM->getEvents(GOLEFT)) 
		{
			lBody = LEFT;
			state = MOVING;
		}
		else if (iInputM->getEvents(GOUP) && iInputM->getEvents(GORIGHT) && !iInputM->getEvents(GODOWN) && iInputM->getEvents(GOLEFT)) 
		{
			lBody = UP;
			state = MOVING;
		}
		else if (!iInputM->getEvents(GOUP) && iInputM->getEvents(GORIGHT) && iInputM->getEvents(GODOWN) && iInputM->getEvents(GOLEFT)) 
		{
			lBody = DOWN;
			state = MOVING;
		}
		else if (iInputM->getEvents(GOUP) && iInputM->getEvents(GORIGHT) && !iInputM->getEvents(GODOWN) && !iInputM->getEvents(GOLEFT)) 
		{
			mDiagonals = NE;
			lBody = RIGHT;
			state = MOVING;
		}
		else if (!iInputM->getEvents(GOUP) && iInputM->getEvents(GORIGHT) && iInputM->getEvents(GODOWN) && !iInputM->getEvents(GOLEFT)) 
		{
			mDiagonals = SE;
			lBody = RIGHT;
			state = MOVING;
		}
		else if (!iInputM->getEvents(GOUP) && !iInputM->getEvents(GORIGHT) && iInputM->getEvents(GODOWN) && iInputM->getEvents(GOLEFT)) 
		{
			mDiagonals = SW;
			lBody = LEFT;
			state = MOVING;
		}
		else if (iInputM->getEvents(GOUP) && !iInputM->getEvents(GORIGHT) && !iInputM->getEvents(GODOWN) && iInputM->getEvents(GOLEFT)) 
		{
			mDiagonals = NW;
			lBody = LEFT;
			state = MOVING;
		}
		else state = MOVING;

		if (!iInputM->getEvents(SHOOTUP) && !iInputM->getEvents(SHOOTRIGHT) && !iInputM->getEvents(SHOOTDOWN) && !iInputM->getEvents(SHOOTLEFT)) hstate = IDLE;
		else hstate = MOVING;

		if (state != IDLE)
		{
			frame += iVideo->getDeltaTime();
			if (frame > 900)
			{
				frame = 0;
			}
			float moveX = 0.0f;
			float moveY = 0.0f;

			float deltaMove = iVideo->getDeltaTime() / 8.5f;
			float deltaMoveDiagonal = iVideo->getDeltaTime() / 12.0f;
			switch (mDiagonals)
			{
			case NONE:
				switch (lBody)
				{
				case DOWN:
					moveY = deltaMove * stats[SPEED];
					break;
				case RIGHT:
					moveX = deltaMove * stats[SPEED];
					break;
				case UP:
					moveY = -(deltaMove * stats[SPEED]);
					break;
				case LEFT:
					moveX = -(deltaMove * stats[SPEED]);
					break;
				default:
					break;
				}
				break;
			case NE:
				moveY = -(deltaMoveDiagonal * stats[SPEED]);
				moveX = deltaMoveDiagonal * stats[SPEED];
				break;
			case SE:
				moveY = deltaMoveDiagonal * stats[SPEED];
				moveX = deltaMoveDiagonal * stats[SPEED];
				break;	 
			case SW:	 
				moveY = deltaMoveDiagonal * stats[SPEED];
				moveX = -(deltaMoveDiagonal * stats[SPEED]);
				break;	 
			case NW:	 
				moveY = -(deltaMoveDiagonal * stats[SPEED]);
				moveX = -(deltaMoveDiagonal * stats[SPEED]);
				break;
			default:
				break;
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
			col.x += realX;
			if (!iRoomM->getActualRoom()->roomWalkable(&col))
			{
				col.x -= realX;
			}
			else
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

			if (col.restY + decimY >= 1)
			{
				realY += 1;
			}
			else if (col.restY + decimY <= -1)
			{
				realY -= 1;
			}
			col.y += realY;
			if (!iRoomM->getActualRoom()->roomWalkable(&col))
			{
				col.y -= realY;
			}
			else
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
			std::cout << moveX << "    " << moveY << "                        " << col.restX << "    " << col.restY << "                        " << col.x << "    " << col.y << std::endl;
		}
		if (hstate == MOVING)
		{
			if (cooldown <= 0)
			{
				shooting = true;
				cooldown = 500;
			}
		}









		// Cap i cos es segueixen
		paint.x = col.x - 6;
		paint.y = col.y - 2;
		switch (iSceneD->getSelectedCharacter())
		{
		case ISAAC:
		case CAIN:
			Head.x = paint.x - 10;
			Head.y = paint.y - Head.h * 2 + 10;
			break;
		case MAGDALENE:
			Head.x = paint.x - 20;
			Head.y = paint.y - Head.h * 2 + 16;
			break;
		case SAMSON:
			Head.x = paint.x - 12;
			Head.y = paint.y - Head.h * 2 + 12;
			break;
		default:
			break;
		}

		if (state == IDLE)
		{
			lBody = DOWN;
			frame = 0;
		}
		if (hstate == IDLE)
		{
			lHead = lBody;
		}
	}
}

void Player::init()
{
	stats[DAMAGE] = 3.5f;
	stats[TEARS] = 0;
	stats[RANGE] = 6.5f;
	stats[SHOT_SPEED] = 1;
	stats[SPEED] = 1;
	stats[LUCK] = 0;
	stats[LIFE_CAPACITY] = 6;
	hp = 6;

	state = IDLE;
	hstate = IDLE;
	lBody = DOWN;
	lHead = DOWN;
	mDiagonals = NONE;

	shooting = false;
	frame = 0;
	cooldown = 0;

	col.w = 24;
	col.h = 24;
	col.x = SCREEN_WIDTH / 2 - col.w / 2;
	col.y = SCREEN_HEIGHT / 2 - col.h / 2;
	Head.w = 28;
	Head.h = 25;
	paint.w = 18;
	paint.h = 15;
	paint.x = col.x - 6;
	paint.y = col.y - 2;
	Head.x = paint.x - 10;
	Head.y = paint.y - Head.h * 2 + 10;

	gID = iResourceM->loadAndGetGraphicID("Assets\\Characters\\Body.png");
	gFrame = iResourceM->loadAndGetGraphicID("Assets\\Characters\\Frame.png");


	switch (iSceneD->getSelectedCharacter())
	{
	case ISAAC:
		pHead = iResourceM->loadAndGetGraphicID("Assets\\Characters\\IsaacHead.png");
		pMisc = iResourceM->loadAndGetGraphicID("Assets\\Characters\\IsaacMisc.png");
		break;
	case MAGDALENE:
		stats[SPEED] = 0.85f;
		stats[LIFE_CAPACITY] = 8;
		hp = 8;
		Head.w = 37;
		Head.h = 32;
		Head.x = paint.x - 20;
		Head.y = paint.y - Head.h * 2 + 16;
		pHead = iResourceM->loadAndGetGraphicID("Assets\\Characters\\MagdeleneHead.png");
		pMisc = iResourceM->loadAndGetGraphicID("Assets\\Characters\\MagdeleneMisc.png");
		break;
	case CAIN:
		stats[RANGE] = 4.5f;
		stats[SPEED] = 1.3f;
		stats[LIFE_CAPACITY] = 4;
		hp = 4;
		pHead = iResourceM->loadAndGetGraphicID("Assets\\Characters\\CainHead.png");
		pMisc = iResourceM->loadAndGetGraphicID("Assets\\Characters\\CainMisc.png");
		break;
	case SAMSON:
		stats[RANGE] = 5;
		stats[TEARS] = 0.1f;
		stats[SHOT_SPEED] = 1.31f;
		stats[SPEED] = 1.1f;
		Head.w = 30;
		Head.h = 27;
		Head.x = paint.x - 12;
		Head.y = paint.y - Head.h * 2 + 12;
		pHead = iResourceM->loadAndGetGraphicID("Assets\\Characters\\SamsonHead.png");
		pMisc = iResourceM->loadAndGetGraphicID("Assets\\Characters\\SamsonMisc.png");
		break;
	default:
		break;
	}
}

Player::Player()
{
	//Stats
	for (int i = 0; i < STAT_LENGHT; i++)
	{
		stats[i] = 0;
	}

	//States
	state = IDLE;
	hstate = IDLE;
	lBody = DOWN;
	lHead = DOWN;
	mDiagonals = NONE;

	//Variables
	shooting = false;
	frame = 0;
	cooldown = 0;
	hp = 6;
	
	//SDL_Rects
	col = {0,0,0,0};
	Head = {0,0,0,0};
	paint = {0,0,0,0};

	//Graphics
	gID = -1;
	gFrame = -1;
	pHead = -1;
	pMisc = -1;

}
