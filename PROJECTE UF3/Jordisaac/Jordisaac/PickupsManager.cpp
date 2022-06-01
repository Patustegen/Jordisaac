#include "PickupsManager.h"
#include "Singletons.h"

PickupsManager* PickupsManager::pInstance = NULL;

PickupsManager::PickupsManager()
{
	pickups.resize(0);
	_p = nullptr;
	sID[0] = iSoundM->loadAndGetSoundID("Assets/Sounds/pennydrop.mp3");
	sID[1] = iSoundM->loadAndGetSoundID("Assets/Sounds/Key_drop0.mp3");
	sID[2] = iSoundM->loadAndGetSoundID("Assets/Sounds/nickeldrop.mp3");
	sID[3] = iSoundM->loadAndGetSoundID("Assets/Sounds/dimedrop.mp3");
	sID[4] = iSoundM->loadAndGetSoundID("Assets/Sounds/pennypickup.mp3");
	sID[5] = iSoundM->loadAndGetSoundID("Assets/Sounds/Keypickup.mp3");
	sID[6] = iSoundM->loadAndGetSoundID("Assets/Sounds/nickelpickup.mp3");
	sID[7] = iSoundM->loadAndGetSoundID("Assets/Sounds/dimepickup.mp3");
	sID[11] = iSoundM->loadAndGetSoundID("Assets/Sounds/superholy.mp3");
}

void PickupsManager::AddPickup(int x, int y, PICKUP_TYPE t, int i)
{
	if (i == -1)
	{
		switch (t)
		{
		case NORMAL_PU:
			i = rand() % 13;
			if (i == 0) iAudio->playAudio(iSoundM->getSoundByID(sID[0]));
			else if (i == 2) iAudio->playAudio(iSoundM->getSoundByID(sID[1]));
			else if (i == 4) iAudio->playAudio(iSoundM->getSoundByID(sID[2]));
			else if (i == 5) iAudio->playAudio(iSoundM->getSoundByID(sID[3]));
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
							if (pickups[i]->getId() == 0) iAudio->playAudio(iSoundM->getSoundByID(sID[4]));
							else if (pickups[i]->getId() == 2) iAudio->playAudio(iSoundM->getSoundByID(sID[5]));
							delete pickups[i];
							pickups.erase(pickups.begin() + i);
							i--;
						}
						break;
					case 3:
						if (_p->PickupUp(1, 2))
						{
							delete pickups[i];
							pickups.erase(pickups.begin() + i);
							i--;
						}
						break;
					case 4:
						if (_p->PickupUp(0, 5))
						{
							iAudio->playAudio(iSoundM->getSoundByID(sID[6]));
							delete pickups[i];
							pickups.erase(pickups.begin() + i);
							i--;
						}
						break;
					case 5:
						if (_p->PickupUp(0, 10))
						{
							iAudio->playAudio(iSoundM->getSoundByID(sID[7]));
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
							iAudio->playAudio(iSoundM->getSoundByID(sID[11]));
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