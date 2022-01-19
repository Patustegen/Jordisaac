#include "Player.h"

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
		else state = MOVING;

		if (!iInputM->getEvents(SHOOTUP) && !iInputM->getEvents(SHOOTRIGHT) && !iInputM->getEvents(SHOOTDOWN) && !iInputM->getEvents(SHOOTLEFT)) hstate = IDLE;
		else hstate = MOVING;

		if (state == MOVING)
		{
			frame += iVideo->getDeltaTime();
			if (frame > 900)
			{
				frame = 0;
			}
		}
		if (hstate == MOVING)
		{
			if (cooldown <= 0)
			{
				shooting = true;
				cooldown = 500;
			}
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

Player::Player()
{
	state = IDLE;
	hstate = IDLE;
	lBody = DOWN;
	lHead = DOWN;
	shooting = false;
	frame = 0;
	cooldown = 0;
	gID = iResourceM->loadAndGetGraphicID("Assets\\Characters\\Body.png");
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

	gFrame = iResourceM->loadAndGetGraphicID("Assets\\Characters\\Frame.png");


	switch (iSceneD->getSelectedCharacter())
	{
	case ISAAC:
		pHead = iResourceM->loadAndGetGraphicID("Assets\\Characters\\IsaacHead.png");
		pMisc = iResourceM->loadAndGetGraphicID("Assets\\Characters\\IsaacMisc.png");
		break;
	case MAGDALENE:
		Head.w = 37;
		Head.h = 32;
		Head.x = paint.x - 20;
		Head.y = paint.y - Head.h * 2 + 16;
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
		Head.x = paint.x - 12;
		Head.y = paint.y - Head.h * 2 + 12;
		pHead = iResourceM->loadAndGetGraphicID("Assets\\Characters\\SamsonHead.png");
		pMisc = iResourceM->loadAndGetGraphicID("Assets\\Characters\\SamsonMisc.png");
		break;
	default:
		break;
	}
}
