#include "Player.h"

void Player::render()
{
	iVideo->renderGraphic(gID, paint.x, paint.y, paint.w, paint.h, frame * paint.w, lBody * paint.h);
	iVideo->renderGraphic(pHead, Head.x, Head.y, Head.w, Head.h, shooting * Head.w, lHead * Head.h);
}

void Player::update()
{
	if (state == DEAD)
	{

	}
	else
	{
		if (state == MOVING)
		{
			frame += iVideo->getDeltaTime();
			if ((lBody == UP || lBody == DOWN) && frame > 400)
			{
				frame = 0;
			}
			else if ((lBody == LEFT || lBody == RIGHT) && frame > 900)
			{
				frame = 0;
			}
		}
		for (int i = 0; i < iInputM->getEvents().size(); i++)
		{
			switch (iInputM->getEvents()[i])
			{
			case QUIT:
				iSceneD->changeScene(PAUSE);
				break;
			case GOUP:
				state = MOVING;
				lBody = UP;
				break;
			case GORIGHT:
				state = MOVING;
				lBody = RIGHT;
				break;
			case GODOWN:
				state = MOVING;
				lBody = DOWN;
				break;
			case GOLEFT:
				state = MOVING;
				lBody = LEFT;
				break;
			case SHOOTUP:
				shooting = true;
				lHead = UP;
				break;
			case SHOOTRIGHT:
				shooting = true;
				lHead = RIGHT;
				break;
			case SHOOTDOWN:
				shooting = true;
				lHead = DOWN;
				break;
			case SHOOTLEFT:
				shooting = true;
				lHead = LEFT;
				break;
			case STOPUP:
				if (lBody == UP)
				{
					state = IDLE;
				}
				break;
			case STOPRIGHT:
				if (lBody == RIGHT)
				{
					state = IDLE;
				}
				break;
			case STOPDOWN:
				if (lBody == DOWN)
				{
					state = IDLE;
				}
				break;
			case STOPLEFT:
				if (lBody == LEFT)
				{
					state = IDLE;
				}
				break;
			case STOPSUP:
				if (lHead == UP)
				{
					shooting = false;
				}
				break;
			case STOPSRIGHT:
				if (lHead == RIGHT)
				{
					shooting = false;
				}
				break;
			case STOPSDOWN:
				if (lHead == DOWN)
				{
					shooting = false;
				}
				break;
			case STOPSLEFT:
				if (lHead == LEFT)
				{
					shooting = false;
				}
				break;
			case USEBOMB:
				break;
			case USEITEM:
				break;
			case USECONS:
				break;
			default:
				break;
			}
		}
		if (state == IDLE)
		{
			lBody = DOWN;
			frame = 0;
		}
		if (!shooting)
		{
			lHead = DOWN;
		}
	}
}

Player::Player()
{
	lBody = DOWN;
	lHead = DOWN;
	shooting = false;
	frame = 0;
	gID = iResourceM->loadAndGetGraphicID("Assets\\Characters\\Body.png");
	col.w = 12;
	col.h = 12;
	col.x = SCREEN_WIDTH / 2 - col.w / 2;
	col.y = SCREEN_HEIGHT / 2 - col.h / 2;
	Head.w = 28;
	Head.h = 25;
	paint.w = 18;
	paint.h = 15;
	paint.x = col.x - 3;
	paint.y = col.y - 1;
	Head.x = paint.x - 5;
	Head.y = paint.y - Head.h + 5;
	
	switch (iSceneD->getSelectedCharacter())
	{
	case ISAAC:
		pHead = iResourceM->loadAndGetGraphicID("Assets\\Characters\\IsaacHead.png");
		pMisc = iResourceM->loadAndGetGraphicID("Assets\\Characters\\IsaacMisc.png");
		break;
	case MAGDALENE:
		Head.w = 37;
		Head.h = 32;
		Head.x = paint.x - 10;
		Head.y = paint.y - Head.h + 8;
		pHead = iResourceM->loadAndGetGraphicID("Assets\\Characters\\MagdeleneHead.png");
		pMisc = iResourceM->loadAndGetGraphicID("Assets\\Characters\\MagdeleneMisc.png");
		break;
	case CAIN:
		pHead = iResourceM->loadAndGetGraphicID("Assets\\Characters\\CainHead.png");
		pMisc = iResourceM->loadAndGetGraphicID("Assets\\Characters\\CainMisc.png");
		break;
	case SAMSON:
		Head.w = 30;
		Head.h = 27;
		Head.x = paint.x - 6;
		Head.y = paint.y - Head.h + 6;
		pHead = iResourceM->loadAndGetGraphicID("Assets\\Characters\\SamsonHead.png");
		pMisc = iResourceM->loadAndGetGraphicID("Assets\\Characters\\SamsonMisc.png");
		break;
	default:
		break;
	}
}
