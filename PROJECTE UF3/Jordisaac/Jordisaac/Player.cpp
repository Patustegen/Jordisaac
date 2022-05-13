#include "Player.h"
#include "Singletons.h"

void Player::render()
{
	if (state == IDLE || state == MOVING)
	{
		iVideo->renderGraphic(gID, paint.x, paint.y, paint.w, paint.h, (frame / 100) * paint.w, lBody * paint.h,2,2);
		iVideo->renderGraphic(pHead, Head.x, Head.y, Head.w, Head.h, shooting * Head.w, lHead * Head.h,2,2);
	}
	else 
	{
		iVideo->renderGraphic(pMisc , Misc.x, Misc.y, Misc.w, Misc.h, (frame / 200) * Misc.w, 3 * Misc.h, 2, 2);
	}

	//iVideo->renderGraphic(gFrame, col.x, col.y, col.w, col.h);
}

void Player::update()
{
	if (state == DEAD)
	{
		frame += iVideo->getDeltaTime();
		if (frame >= 400)
		{
			frame = 400;
		}
	}
	else
	{
		if (cooldown > 0)
		{
			if (cooldown <= (500 + stats[TEARS] * 100) -100)
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
		if (iInputM->getEvents(USEBOMB)) 
		{
			if (pickups[1] > 0)
			{
				pickups[1]--;
				iBombM->AddBomb(col.x, col.y);
			}
		}
		if (iInputM->getEvents(USEITEM));
		if (iInputM->getEvents(USECONS));
		
		mDiagonals = NONE;

		if (!iInputM->getEvents(GOUP) && !iInputM->getEvents(GORIGHT) && !iInputM->getEvents(GODOWN) && !iInputM->getEvents(GOLEFT))
		{
			lBody = NO;
			if (state != HURT)
			{
				state = IDLE;
			}
		}
		else if (iInputM->getEvents(GOUP) && !iInputM->getEvents(GORIGHT) && iInputM->getEvents(GODOWN) && !iInputM->getEvents(GOLEFT))
		{
			lBody = NO;
			if (state != HURT)
			{
				state = IDLE;
			}
		}
		else if (!iInputM->getEvents(GOUP) && iInputM->getEvents(GORIGHT) && !iInputM->getEvents(GODOWN) && iInputM->getEvents(GOLEFT))
		{
			lBody = NO;
			if (state != HURT)
			{
				state = IDLE;
			}
		}
		else if (iInputM->getEvents(GOUP) && iInputM->getEvents(GORIGHT) && iInputM->getEvents(GODOWN) && !iInputM->getEvents(GOLEFT)) 
		{
			lBody = RIGHT;
			if (state != HURT )
			{
				state = MOVING;
			}
		}
		else if (iInputM->getEvents(GOUP) && !iInputM->getEvents(GORIGHT) && iInputM->getEvents(GODOWN) && iInputM->getEvents(GOLEFT)) 
		{
			lBody = LEFT;
			if (state != HURT)
			{
				state = MOVING;
			}
		}
		else if (iInputM->getEvents(GOUP) && iInputM->getEvents(GORIGHT) && !iInputM->getEvents(GODOWN) && iInputM->getEvents(GOLEFT)) 
		{
			lBody = UP;
			if (state != HURT)
			{
				state = MOVING;
			}
		}
		else if (!iInputM->getEvents(GOUP) && iInputM->getEvents(GORIGHT) && iInputM->getEvents(GODOWN) && iInputM->getEvents(GOLEFT)) 
		{
			lBody = DOWN;
			if (state != HURT)
			{
				state = MOVING;
			}
		}
		else if (iInputM->getEvents(GOUP) && iInputM->getEvents(GORIGHT) && !iInputM->getEvents(GODOWN) && !iInputM->getEvents(GOLEFT)) 
		{
			mDiagonals = NE;
			lBody = RIGHT;
			if (state != HURT)
			{
				state = MOVING;
			}
		}
		else if (!iInputM->getEvents(GOUP) && iInputM->getEvents(GORIGHT) && iInputM->getEvents(GODOWN) && !iInputM->getEvents(GOLEFT)) 
		{
			mDiagonals = SE;
			lBody = RIGHT;
			if (state != HURT)
			{
				state = MOVING;
			}
		}
		else if (!iInputM->getEvents(GOUP) && !iInputM->getEvents(GORIGHT) && iInputM->getEvents(GODOWN) && iInputM->getEvents(GOLEFT)) 
		{
			mDiagonals = SW;
			lBody = LEFT;
			if (state != HURT)
			{
				state = MOVING;
			}
		}
		else if (iInputM->getEvents(GOUP) && !iInputM->getEvents(GORIGHT) && !iInputM->getEvents(GODOWN) && iInputM->getEvents(GOLEFT)) 
		{
			mDiagonals = NW;
			lBody = LEFT;
			if (state != HURT)
			{
				state = MOVING;
			}
		}
		else
		{
			if (state != HURT)
			{
				state = MOVING;
			}
		}

		if (!iInputM->getEvents(SHOOTUP) && !iInputM->getEvents(SHOOTRIGHT) && !iInputM->getEvents(SHOOTDOWN) && !iInputM->getEvents(SHOOTLEFT)) hstate = IDLE;
		else hstate = MOVING;

		if (state != IDLE)
		{
			frame += iVideo->getDeltaTime();
			if (state == MOVING)
			{
				if (frame > 900)
				{
					frame = 0;
				}
			}
			else if (state == HURT)
			{
				frame -= iVideo->getDeltaTime() / 2;
				if (frame >= 300)
				{
					state = IDLE;
				}
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
			col.x += (int)realX;
			if (!iRoomM->getActualRoom()->roomWalkable(&col))
			{
				col.x -= (int)realX;
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
			col.y += (int)realY;
			if (!iRoomM->getActualRoom()->roomWalkable(&col))
			{
				col.y -= (int)realY;
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
		}
		if (hstate == MOVING)
		{
			if (cooldown <= 0)
			{
				shooting = true;
				cooldown = 500 + (int)stats[TEARS] * 100;
			}
		}

		if (shooting && cooldown == 500 + stats[TEARS] * 100)
		{
			iBulletM->AddBullet(stats[SHOT_SPEED], 1, stats[RANGE], &Head, lHead);
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
		Misc.x = Head.x;
		Misc.y = Head.y;
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
	sHearts.resize(0);
	eHeart = false;

	state = IDLE;
	hstate = IDLE;
	lBody = DOWN;
	lHead = DOWN;
	mDiagonals = NONE;

	shooting = false;
	frame = 0;
	cooldown = 0;
	pickups[0] = 0;
	pickups[1] = 0;
	pickups[2] = 0;

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
	Misc.x = Head.x;
	Misc.y = Head.y;
	Misc.w = 34;
	Misc.h = 33;

	gID = iResourceM->loadAndGetGraphicID("Assets\\Characters\\Body.png");
	gFrame = iResourceM->loadAndGetGraphicID("Assets\\Characters\\Frame.png");

	sID.push_back(iSoundM->loadAndGetSoundID("Assets/Characters/death1.wav"));
	sID.push_back(iSoundM->loadAndGetSoundID("Assets/Characters/death2.wav"));
	sID.push_back(iSoundM->loadAndGetSoundID("Assets/Characters/death3.wav"));
	sID.push_back(iSoundM->loadAndGetSoundID("Assets/Characters/hurt1.wav"));
	sID.push_back(iSoundM->loadAndGetSoundID("Assets/Characters/hurt2.wav"));
	sID.push_back(iSoundM->loadAndGetSoundID("Assets/Characters/hurt3.wav"));

	switch (iSceneD->getSelectedCharacter())
	{
	case ISAAC:
		pickups[1] = 1;
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
		Misc.w = 40;
		Misc.h = 37;
		pHead = iResourceM->loadAndGetGraphicID("Assets\\Characters\\MagdeleneHead.png");
		pMisc = iResourceM->loadAndGetGraphicID("Assets\\Characters\\MagdeleneMisc.png");
		break;
	case CAIN:
		pickups[2] = 1;
		stats[RANGE] = 4.5f;
		stats[SPEED] = 1.3f;
		stats[LIFE_CAPACITY] = 4;
		hp = 4;
		pHead = iResourceM->loadAndGetGraphicID("Assets\\Characters\\CainHead.png");
		pMisc = iResourceM->loadAndGetGraphicID("Assets\\Characters\\CainMisc.png");
		break;
	case SAMSON:
		stats[RANGE] = 5;
		stats[TEARS] = 1;
		stats[SHOT_SPEED] = 1.31f;
		stats[SPEED] = 1.1f;
		Head.w = 30;
		Head.h = 27;
		Misc.w = 38;
		Misc.h = 39;
		Head.x = paint.x - 12;
		Head.y = paint.y - Head.h * 2 + 12;
		pHead = iResourceM->loadAndGetGraphicID("Assets\\Characters\\SamsonHead.png");
		pMisc = iResourceM->loadAndGetGraphicID("Assets\\Characters\\SamsonMisc.png");
		break;
	default:
		break;
	}
	totalHearts = hp;
}

bool Player::PickupUp(int p, int q)
{
	if (pickups[p] + q <= MAX_PICKUP)
	{
		pickups[p] += q;
		return true;
	}
	else if (pickups[p] != MAX_PICKUP)
	{
		pickups[p] = MAX_PICKUP;
		return true;
	}
	return false;
}

bool Player::pickupHeart(HEARTS t)
{
	switch (t)
	{
	case HALF_RED:
		if (hp +1 <= stats[LIFE_CAPACITY])
		{
			hp++;
			return true;
		}
		return false;
		break;
	case FULL_RED:
		if (hp +2 <= stats[LIFE_CAPACITY])
		{
			hp += 2;
			return true;
		}
		return false;
		break;
	case HALF_SOUL:
		if (sHearts.size() == 0)
		{ 
			if (totalHearts + 2 <= MAX_HEARTS)
			{
				sHearts.push_back(t);
				totalHearts++;
				return true;
			}
			return false;
		}
		else
		{
			switch (sHearts[sHearts.size() - 1])
			{
			case HALF_SOUL:
				sHearts[sHearts.size() - 1] = FULL_SOUL;
				totalHearts++;
				return true;
				break;
			case HALF_BLACK:
				sHearts[sHearts.size() - 1] = FULL_BLACK;
				totalHearts++;
				return true;
				break;
			default:
				if (totalHearts + 2 <= MAX_HEARTS)
				{
					sHearts.push_back(t);
					totalHearts++;
					return true;
				}
				return false;
				break;
			}
		}
		break;
	case FULL_SOUL:
		if (sHearts.size() == 0)
		{
			if (totalHearts + 2 <= MAX_HEARTS)
			{
				sHearts.push_back(t);
				totalHearts += 2;
				return true;
			}
			return false;
		}
		else
		{
			switch (sHearts[sHearts.size() - 1])
			{
			case HALF_SOUL:
				if (totalHearts + 2 <= MAX_HEARTS)
				{
					sHearts[sHearts.size() - 1] = t;
					sHearts.push_back(HALF_SOUL);
					totalHearts++;
					return true;
				}
				return false;
				break;
			case HALF_BLACK:
				if (totalHearts + 2 <= MAX_HEARTS)
				{
					sHearts[sHearts.size() - 1] = FULL_BLACK;
					sHearts.push_back(HALF_SOUL);
					totalHearts++;
					return true;
				}
				return false;
				break;
			default:
				if (totalHearts + 2 <= MAX_HEARTS)
				{
					sHearts.push_back(t);
					totalHearts++;
					return true;
				}
				return false;
				break;
			}
		}
		break;
	case FULL_BLACK:
		if (sHearts.size() == 0)
		{
			if (totalHearts + 2 <= MAX_HEARTS)
			{
				sHearts.push_back(t);
				totalHearts++;
				return true;
			}
			return false;
		}
		else
		{
			switch (sHearts[sHearts.size() - 1])
			{
			case HALF_BLACK:
				if (totalHearts + 2 <= MAX_HEARTS)
				{
					sHearts[sHearts.size() - 1] = t;
					sHearts.push_back(HALF_BLACK);
					totalHearts++;
					return true;
				}
				return false;
				break;
			case HALF_SOUL:
				if (totalHearts + 2 <= MAX_HEARTS)
				{
					sHearts[sHearts.size() - 1] = FULL_SOUL;
					sHearts.push_back(HALF_BLACK);
					totalHearts++;
					return true;
				}
				return false;
				break;
			default:
				if (totalHearts + 2 <= MAX_HEARTS)
				{
					sHearts.push_back(t);
					totalHearts++;
					return true;
				}
				return false;
				break;
			}
		}
		break;
	case HALF_ETERNAL:
		if (eHeart)
		{
			if (hp != MAX_HEARTS)
			{
				eHeart = false;
				stats[LIFE_CAPACITY] += 2;
				hp += 2;
				if (totalHearts == MAX_HEARTS)
				{
					for (int i = 0; i < sHearts.size() -1; i++)
					{
						sHearts[i] = sHearts[i + 1];
					}
					sHearts.pop_back();
					return true;
				}
				else if (totalHearts +1 == MAX_HEARTS)
				{
					sHearts.pop_back();
					totalHearts = MAX_HEARTS;
					return true;
				}
				else
				{
					totalHearts++;
					return true;
				}
			}
			return false;
		}
		else 
		{ 
			eHeart = true;
			return true;
		}
		break;
	default:
		break;
	}
}

bool Player::getHurt()
{
	switch (state)
	{
	case IDLE:
	case MOVING:
		if (sHearts.size() > 0)
		{
			totalHearts--;
			switch (sHearts[sHearts.size() - 1])
			{
			case HALF_SOUL:
				sHearts.pop_back();
				break;
			case FULL_SOUL:
				sHearts[sHearts.size() - 1] = HALF_SOUL;
				break;
			case HALF_BLACK:
				sHearts.pop_back();
				iRoomM->getActualRoom()->damageAll();
				break;
			case FULL_BLACK:
				sHearts[sHearts.size() - 1] = HALF_BLACK;
				break;
			default:
				break;
			}
		}
		else
		{
			if (eHeart) eHeart = false;
			else hp--;
		}
		frame = 0;
		if (hp == 0 && sHearts.size() == 0)
		{
			state = DEAD;
			iAudio->playAudio(iSoundM->getSoundByID(sID[rand() % 3]),3);
		}
		else
		{
			state = HURT;
			iAudio->playAudio(iSoundM->getSoundByID(sID[rand() % 3 + 3]));
		}
		return true;
		break;
	default:
		break;
	}
	return false;
}

Player::Player()
{
	//Stats
	for (int i = 0; i < STAT_LENGHT; i++)
	{
		stats[i] = 0;
	}
	sHearts.resize(0);
	eHeart = false;
	totalHearts = hp;

	//Pickups
	for (int i = 0; i < 3; i++)
	{
		pickups[i] = 0;
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
	
	//Rects
	col = {0,0,0,0};
	Head = {0,0,0,0};
	paint = {0,0,0,0};
	Misc = { 0,0,0,0 };

	//Graphics
	gID = -1;
	gFrame = -1;
	pHead = -1;
	pMisc = -1;

}

Player::~Player()
{
}
