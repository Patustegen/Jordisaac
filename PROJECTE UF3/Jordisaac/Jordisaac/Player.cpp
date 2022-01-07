#include "Player.h"

void Player::render()
{
	iVideo->renderGraphic(gID, paint.x, paint.y, paint.w, paint.h, frame * paint.w, lBody * paint.h);
	iVideo->renderGraphic(pHead, Head.x, Head.y, Head.w, Head.h, shooting * Head.w, lHead * Head.h);
}

void Player::update()
{
	for (int i = 0; i < iInputM->getEvents().size(); i++)
	{
		switch (iInputM->getEvents()[i])
		{
		case QUIT:
			iSceneD->changeScene(PAUSE);
			break;
		case GOUP:
			lBody = UP;
			break;
		case GORIGHT:
			lBody = RIGHT;
			break;
		case GODOWN:
			lBody = DOWN;
			break;
		case GOLEFT:
			lBody = LEFT;
			break;
		case SHOOTUP:
			lHead = UP;
			break;
		case SHOOTRIGHT:
			lHead = RIGHT;
			break;
		case SHOOTDOWN:
			lHead = DOWN;
			break;
		case SHOOTLEFT:
			lHead = LEFT;
			break;
		case USEBOMB:
			break;
		case USEITEM:
			break;
		case USECONS:
			break;
		case ENTER:
			break;
		default:
			break;
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
		break;
	case CAIN:
		break;
	case SAMSON:
		break;
	default:
		break;
	}
}
