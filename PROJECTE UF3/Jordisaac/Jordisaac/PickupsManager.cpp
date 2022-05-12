#include "PickupsManager.h"
#include "Singletons.h"

PickupsManager* PickupsManager::pInstance = NULL;

PickupsManager::PickupsManager()
{
	pickups.resize(0);
}

void PickupsManager::AddPickup(int x, int y, int t)
{
	if (t == -1) t = rand() % 13;
	Pickup* nPickup = new Pickup(x, y, t);
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
				case 0:
				case 1:
				case 2:
					_p->PickupUp(pickups[i]->getType());
					break;
				case 3:
					_p->PickupUp(1, 2);
					break;
				case 4:
					_p->PickupUp(0, 5);
					break;
				case 5:
					_p->PickupUp(0, 10);
					break;
				case 6:
					//Battery
					break;
				//CORS
				case 7:
					
					break;
				case 8:
					break;
				case 9:
					break;
				case 10:
					break;
				case 11:
					break;
				case 12:
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