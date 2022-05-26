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
							pickups.erase(pickups.begin() + i);
							i--;
						}
						break;
					case 3:
						if (_p->PickupUp(1, 2))
						{
							//sound
							pickups.erase(pickups.begin() + i);
							i--;
						}
						break;
					case 4:
						if (_p->PickupUp(0, 5))
						{
							//sound
							pickups.erase(pickups.begin() + i);
							i--;
						}
						break;
					case 5:
						if (_p->PickupUp(0, 10))
						{
							//sound
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
							pickups.erase(pickups.begin() + i);
							i--;
						}
						break;
					case 8:
						if (_p->pickupHeart(FULL_RED))
						{
							pickups.erase(pickups.begin() + i);
							i--;
						}
						break;
					case 9:
						if (_p->pickupHeart(HALF_SOUL))
						{
							pickups.erase(pickups.begin() + i);
							i--;
						}
						break;
					case 10:
						if (_p->pickupHeart(FULL_SOUL))
						{
							pickups.erase(pickups.begin() + i);
							i--;
						}
						break;
					case 11:
						if (_p->pickupHeart(FULL_BLACK))
						{
							pickups.erase(pickups.begin() + i);
							i--;
						}
						break;
					case 12:
						if (_p->pickupHeart(HALF_ETERNAL))
						{
							pickups.erase(pickups.begin() + i);
							i--;
						}
						break;
					default:
						break;
					}
					break;
				case CONS_PU:
					switch (pickups[i]->getId())
					{
					case 0:
						break;
					case 1:
						break;
					case 2:
						break;
					case 3:
						break;
					case 4:
						break;
					case 5:
						break;
					default:
						break;
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