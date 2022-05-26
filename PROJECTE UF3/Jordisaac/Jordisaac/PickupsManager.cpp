#include "PickupsManager.h"
#include "Singletons.h"

PickupsManager* PickupsManager::pInstance = NULL;

PickupsManager::PickupsManager()
{
	pickups.resize(0);
	_p = nullptr;
}

void PickupsManager::AddPickup(int x, int y, PICKUP_TYPE t, int i)
{
	if (i == -1)
	{
		switch (t)
		{
		case NORMAL_PU:
			i = rand() % 13;
			break;
		case CONS_PU:
			i = rand() % 6;
			break;
		case PASSIVE_PU:
			break;
		case ACTIVE_PU:
			break;
		case TRINKET_PU:
			break;
		default:
			break;
		}
	}
	Pickup* nPickup = new Pickup(x, y, i, t);
	pickups.push_back(nPickup);
}

void PickupsManager::init()
{
	for (int i = 0; i < pickups.size(); i++)
	{
		delete pickups[i];
		pickups.erase(pickups.begin() + i);
		i--;
	}
	pickups.resize(0);
	for (int i = 0; i < 6; i++)
	{
		bool bad;
		do
		{
			bad = false;
			pills[i] = rand() % 6;
			for (int j = 0; j < i; j++)
			{
				if (pills[j] == pills[i]) bad = true;
			}
		} while (bad);
	}
}

void PickupsManager::update()
{
	for (int i = 0; i < pickups.size(); i++)
	{
		if (pickups[i]->getRoom() == iRoomM->getActualRoom()->getRoomID())
		{
			if (iVideo->onCollision(pickups[i]->getCol(), _p->getCol()))
			{
				switch (pickups[i]->getType())
				{
				case NORMAL_PU:
					switch (pickups[i]->getId())
					{
					case 0:
					case 1:
					case 2:
						if (_p->PickupUp(pickups[i]->getId()))
						{
							//sound
							delete pickups[i];
							pickups.erase(pickups.begin() + i);
							i--;
						}
						break;
					case 3:
						if (_p->PickupUp(1, 2))
						{
							//sound
							delete pickups[i];
							pickups.erase(pickups.begin() + i);
							i--;
						}
						break;
					case 4:
						if (_p->PickupUp(0, 5))
						{
							//sound
							delete pickups[i];
							pickups.erase(pickups.begin() + i);
							i--;
						}
						break;
					case 5:
						if (_p->PickupUp(0, 10))
						{
							//sound
							delete pickups[i];
							pickups.erase(pickups.begin() + i);
							i--;
						}
						break;
					case 6:
						//Battery
						break;
						//CORS
					case 7:
						if (_p->pickupHeart(HALF_RED))
						{
							delete pickups[i];
							pickups.erase(pickups.begin() + i);
							i--;
						}
						break;
					case 8:
						if (_p->pickupHeart(FULL_RED))
						{
							delete pickups[i];
							pickups.erase(pickups.begin() + i);
							i--;
						}
						break;
					case 9:
						if (_p->pickupHeart(HALF_SOUL))
						{
							delete pickups[i];
							pickups.erase(pickups.begin() + i);
							i--;
						}
						break;
					case 10:
						if (_p->pickupHeart(FULL_SOUL))
						{
							delete pickups[i];
							pickups.erase(pickups.begin() + i);
							i--;
						}
						break;
					case 11:
						if (_p->pickupHeart(FULL_BLACK))
						{
							delete pickups[i];
							pickups.erase(pickups.begin() + i);
							i--;
						}
						break;
					case 12:
						if (_p->pickupHeart(HALF_ETERNAL))
						{
							delete pickups[i];
							pickups.erase(pickups.begin() + i);
							i--;
						}
						break;
					default:
						break;
					}
					break;
				case CONS_PU:
					if (_p->getCons()->getType() != -1)
					{
						int x = _p->getCol()->x + _p->getCol()->w / 2 - pickups[i]->getCol()->w / 2;
						int y = _p->getCol()->y + _p->getCol()->h + pickups[i]->getCol()->h;
						if (y > SCREEN_HEIGHT - ROOM_MARGIN_Y) y = _p->getCol()->y - _p->getCol()->h - 20;
						AddPickup(x, y, CONS_PU, _p->getCons()->getType());
						_p->getCons()->setPill(pills[pickups[i]->getId()], pickups[i]->getId());
						delete pickups[i];
						pickups.erase(pickups.begin() + i);
						i--;
					}
					else
					{
						_p->getCons()->setPill(pills[pickups[i]->getId()], pickups[i]->getId());
						delete pickups[i];
						pickups.erase(pickups.begin() + i);
						i--;
					}
					break;
				case PASSIVE_PU:
					break;
				case ACTIVE_PU:
					break;
				case TRINKET_PU:
					break;
				default:
					break;
				}
			}
		}
	}
}

void PickupsManager::render()
{
	for (int i = 0; i < pickups.size(); i++)
	{
		if (pickups[i]->getRoom() == iRoomM->getActualRoom()->getRoomID()) pickups[i]->render();
	}
}