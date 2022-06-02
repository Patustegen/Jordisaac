#include "Room.h"
#include "Singletons.h"
#include "AttackFly.h"
#include "Pooter.h"
#include "Hollow.h"

#define DOOR_MARGIN 15

void Room::init(Player* p)
{
	_player = p;
	if (rID != 0)
	{
		switch (roomType)
		{
		case NORMAL:
			if (!completed)
			{
				int max = rand() % 3 + iRoomM->getActualLevel();
				for (int i = 0; i < max; i++)
				{
					AttackFly* nFly = new AttackFly(rand()%400 + 200, rand()%200 + 200);
					nFly->setPlayer(p);
					enemies.push_back(nFly);
				}
				for (int i = 0; i < 1 + iRoomM->getActualLevel(); i++)
				{
					Pooter* nPoot = new Pooter(rand()%400 + 200, rand()%200 + 200);
					nPoot->setPlayer(p);
					enemies.push_back(nPoot);
				}
			}
			break;
		case BOSS:
			if (!completed)
			{
				iAudio->haltChannel();
				iAudio->playAudio(iSoundM->getSoundByID(bossMusic), 0);
				bossType = rand() % 3;
				bossType = 0;
				switch (bossType)
				{
				case 0:
					boss = new Hollow();
					break;
				case 1:
					break;
				case 2:
					break;
				default:
					break;
				}
				boss->init();
			}
			break;
		case GOLDEN:
			if (completed == false)
			{
				completed = true;
				iPickM->AddPickup(SCREEN_WIDTH / 2 - 10, SCREEN_HEIGHT / 2 - 10, CONS_PU, rand() % 6);
			}
			break;
		default:
			break;
		}
	}
	else
	{
		if (completed == false)
		{
			completed = true;
		}
	}
	movCharacters.push_back(_player);
	for (int i = 0; i < enemies.size(); i++)
	{
		movCharacters.push_back(enemies[i]);
	}
	iBulletM->init();
	iBombM->init();
}

void Room::update()
{
	_player->update();
	iBulletM->update();
	iBombM->update();
	iPickM->update();

	if (completed)
	{
		movCharacters.resize(0);
		movCharacters.push_back(_player);
		bool swapped = false;
		do
		{
			swapped = true;
			for (int i = 1; i < movCharacters.size(); i++)
			{
				if (movCharacters[i - 1]->getCol()->y + movCharacters[i - 1]->getCol()->h > movCharacters[i]->getCol()->y + movCharacters[i]->getCol()->h)
				{
					BaseCharacter* tmp = movCharacters[i - 1];
					movCharacters[i - 1] = movCharacters[i];
					movCharacters[i] = tmp;
					swapped = false;
				}
			}
		} while (!swapped);
		for (int i = 0; i < colDoor.size(); i++)
		{
			if (iVideo->isInside(&colDoor[i].col, _player->getCol()))
			{
				iRoomM->changeRoom(rID,colDoor[i].idChange, _player);
			}
		}
	}
	else
	{
		movCharacters.resize(0);
		movCharacters.push_back(_player);
		if (roomType == NORMAL)
		{
			for (int i = 0; i < enemies.size(); i++)
			{
				enemies[i]->update();
				if (iVideo->onCollision(_player->getCol(), enemies[i]->getCol())) _player->getHurt();
				if (enemies[i]->getHP() <= 0)
				{
					_player->giveScore(enemies[i]->getPoints());
					delete enemies[i];
					enemies.erase(enemies.begin() + i);
					i--;
				}
			}
			
			if (enemies.size() == 0)
			{
				completed = true;
				movCharacters.resize(0);
				movCharacters.push_back(_player);
				int type = rand() % 2;
				if (type == 0)
				{
					int max = rand() % 2 + (_player->getStat(LUCK) / 2);
					for (int i = 0; i < max; i++)
					{
						iPickM->AddPickup((SCREEN_WIDTH / 2) - (rand() % 15 - 10), (SCREEN_HEIGHT / 2) - (rand() % 15 - 10), NORMAL_PU);
					}
				}
				else
				{
					iPickM->AddPickup((SCREEN_WIDTH / 2) - (rand() % 15 - 10), (SCREEN_HEIGHT / 2) - (rand() % 15 - 10), CONS_PU);
				}
			}
		}
		else if (roomType == BOSS)
		{
			boss->update();
			if (boss->getHP() <= 0)
			{
				_player->giveScore(boss->getPoints());
				delete boss;
				completed = true;
				int type = rand() % 2;
				if (type == 0)
				{
					int max = rand() % 2 + (_player->getStat(LUCK) / 2);
					for (int i = 0; i < max; i++)
					{
						int heart = rand() % 6 + 7;
						iPickM->AddPickup((SCREEN_WIDTH / 2) - (rand() % 15 - 10), (SCREEN_HEIGHT / 2) - (rand() % 15 - 10), NORMAL_PU, heart);
					}
				}
				else
				{
					iPickM->AddPickup((SCREEN_WIDTH / 2) - (rand() % 15 - 10), (SCREEN_HEIGHT / 2) - (rand() % 15 - 10), CONS_PU);
				}
			}
			else movCharacters.push_back(boss);
		}
		bool swapped = false;
		for (int i = 0; i < enemies.size(); i++) movCharacters.push_back(enemies[i]);
		do
		{
			swapped = true;
			for (int i = 1; i < movCharacters.size(); i++)
			{
				if (movCharacters[i - 1]->getCol()->y + movCharacters[i - 1]->getCol()->h > movCharacters[i]->getCol()->y + movCharacters[i]->getCol()->h)
				{
					BaseCharacter* tmp = movCharacters[i - 1];
					movCharacters[i - 1] = movCharacters[i];
					movCharacters[i] = tmp;
					swapped = false;
				}
			}
		} while (!swapped);
	}
}

void Room::render()
{
	iVideo->renderGraphic(bg, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
	switch (roomType)
	{
	case NORMAL:
		for (int i = 0; i < colDoor.size(); i++)
		{
			iVideo->renderGraphicEx(gDoor, &colDoor.at(i).paint, colDoor.at(i).angle, 2.0f, 2.0f, colDoor.at(i).paint.w * completed, colDoor.at(0).paint.h * colDoor.at(i).nRoom);
		}
		break;
	case BOSS:
		for (int i = 0; i < colDoor.size(); i++)
		{
			if (colDoor[i].idChange == 10000)
			{
				if (completed) iVideo->renderGraphic(gTDoor, colDoor[i].paint.x, colDoor[i].paint.y, colDoor[i].paint.w, colDoor[i].paint.h, 0, 0, 0.25f, 0.25f);
			}
			else iVideo->renderGraphicEx(gDoor, &colDoor.at(i).paint, colDoor.at(i).angle, 2.0f, 2.0f, colDoor.at(i).paint.w * completed, colDoor.at(i).paint.h);
		}
		break;
	case GOLDEN:
		iVideo->renderGraphicEx(gDoor, &colDoor.at(0).paint, colDoor.at(0).angle, 2.0f, 2.0f, colDoor.at(0).paint.w * completed, colDoor.at(0).paint.h * 2);
		break;
	default:
		break;
	}
	iBombM->render();
	iPickM->render();
	for (int i = 0; i < movCharacters.size(); i++)
	{
		movCharacters[i]->render();
	}
	iBulletM->render();
}

bool Room::roomWalkable(Rect* col)
{
	for (int i = 0; i < colDoor.size(); i++)
	{
		if (completed && iVideo->onCollision(col, &colDoor[i].col))
		{
			return true;
		}
	}
	if (col->x < ROOM_MARGIN_X || (col->x > SCREEN_WIDTH - ROOM_MARGIN_X - col->w) || col->y < ROOM_MARGIN_Y || (col->y > SCREEN_HEIGHT - ROOM_MARGIN_Y - col->h))
	{
		return false;
	}
	return true;
}

bool Room::colWalkable(Rect* col)
{
	int touches = -1;
	for (int i = 0; i < enemies.size(); i++)
	{
		if (col->x != enemies[i]->getCol()->x && col->y != enemies[i]->getCol()->y)
		{
			if (iVideo->onCollision(col, enemies[i]->getCol()))
			{
				return false;
			}
		}
	}
	return true;
}

bool Room::enemyCol(Rect* col, int* enemyID)
{
	for (int i = 0; i < enemies.size(); i++)
	{
		if (iVideo->onCollision(col, enemies[i]->getCol())) 
		{ 
			*enemyID = i;
			return true; 
		}
	}
	return false;
}

bool Room::playerCol(Rect* col)
{
	if (iVideo->onCollision(col, _player->getCol())) return true;
	return false;
}

void Room::damageAll()
{
	for (int i = 0; i < enemies.size(); i++)enemies[i]->hurt();
}

Room::Room(int nDoors, int roomID)
{
	bossType = -1;
	bossMusic = -1;
	int doorCount = 0;
	roomType = NORMAL;
	_player = nullptr;
	boss = nullptr;
	completed = false;
	movCharacters.resize(0);
	colDoor.resize(0);
	enemies.resize(0);
	rID = roomID;
	if(iRoomM->getbgID() == 0) bg = iResourceM->loadAndGetGraphicID("Assets\\Rooms\\BasementDefault.png");
	else if (iRoomM->getbgID() == 1) bg = iResourceM->loadAndGetGraphicID("Assets\\Rooms\\CavesDefault.png");
	else if (iRoomM->getbgID() == 2) bg = iResourceM->loadAndGetGraphicID("Assets\\Rooms\\DepthsDefault.png");
	gDoor = iResourceM->loadAndGetGraphicID("Assets\\Rooms\\doorsImages.png");
	gTDoor = iResourceM->loadAndGetGraphicID("Assets\\Rooms\\trapdoor.png");


	if (nDoors & 0x01)
	{
		doorCount++;
		Door nDoor;
		nDoor.col = { SCREEN_WIDTH / 2 - DOOR_W, DOOR_MARGIN, DOOR_W * 2, DOOR_H * 2 };
		nDoor.paint = { SCREEN_WIDTH / 2 - DOOR_W, DOOR_MARGIN, DOOR_W, DOOR_H };
		nDoor.angle = 0.0;
		nDoor.idChange = -10;
		colDoor.push_back(nDoor);
		if (roomID == 0)
		{
			doorCount++;
			Door nDoor;
			nDoor.col = { SCREEN_WIDTH / 2 - DOOR_W, SCREEN_HEIGHT - DOOR_H * 2 - DOOR_MARGIN, DOOR_W * 2, DOOR_H * 2 };
			nDoor.paint = { SCREEN_WIDTH / 2 - DOOR_W, SCREEN_HEIGHT - DOOR_H * 2 - DOOR_MARGIN, DOOR_W, DOOR_H };
			nDoor.angle = 180.0;
			nDoor.idChange = 10;
			if (iRoomM->getActualLevel() != 1) nDoor.locked = true;
			nDoor.nRoom = GOLDEN;
			colDoor.push_back(nDoor);
		}
	}
	if (nDoors & 0x02)
	{
		doorCount++;
		Door nDoor;
		nDoor.col = { SCREEN_WIDTH / 2 - DOOR_W, SCREEN_HEIGHT - DOOR_H * 2 - DOOR_MARGIN, DOOR_W * 2, DOOR_H * 2 };
		nDoor.paint = { SCREEN_WIDTH / 2 - DOOR_W, SCREEN_HEIGHT - DOOR_H * 2 - DOOR_MARGIN, DOOR_W, DOOR_H };
		nDoor.angle = 180.0;
		nDoor.idChange = 10;
		colDoor.push_back(nDoor);
		if (roomID == 0)
		{
			doorCount++;
			Door nDoor;
			nDoor.col = { SCREEN_WIDTH / 2 - DOOR_W, DOOR_MARGIN, DOOR_W * 2, DOOR_H * 2 };
			nDoor.paint = { SCREEN_WIDTH / 2 - DOOR_W, DOOR_MARGIN, DOOR_W, DOOR_H };
			nDoor.angle = 0.0;
			nDoor.idChange = -10;
			if (iRoomM->getActualLevel() != 1) nDoor.locked = true;
			nDoor.nRoom = GOLDEN;
			colDoor.push_back(nDoor);
		}
	}
	if (nDoors & 0x04)
	{
		doorCount++;
		Door nDoor;
		nDoor.col = { SCREEN_WIDTH - DOOR_W * 2 - DOOR_MARGIN, SCREEN_HEIGHT / 2 - DOOR_H, DOOR_W * 2, DOOR_H * 2 };
		nDoor.paint = { SCREEN_WIDTH - DOOR_W * 2 - DOOR_MARGIN, SCREEN_HEIGHT / 2 - DOOR_H, DOOR_W, DOOR_H };
		nDoor.angle = 90.0;
		nDoor.idChange = 1;
		colDoor.push_back(nDoor);
		if (roomID == 0)
		{
			doorCount++;
			Door nDoor;
			nDoor.col = { DOOR_MARGIN, SCREEN_HEIGHT / 2 - DOOR_H, DOOR_W * 2, DOOR_H * 2 };
			nDoor.paint = { DOOR_MARGIN, SCREEN_HEIGHT / 2 - DOOR_H, DOOR_W, DOOR_H };
			nDoor.angle = 270.0;
			nDoor.idChange = -1;
			if (iRoomM->getActualLevel() != 1) nDoor.locked = true;
			nDoor.nRoom = GOLDEN;
			colDoor.push_back(nDoor);
		}
	}
	if (nDoors & 0x08)
	{
		doorCount++;
		Door nDoor;
		nDoor.col = { DOOR_MARGIN, SCREEN_HEIGHT / 2 - DOOR_H, DOOR_W * 2, DOOR_H * 2 };
		nDoor.paint = { DOOR_MARGIN, SCREEN_HEIGHT / 2 - DOOR_H, DOOR_W, DOOR_H };
		nDoor.angle = 270.0;
		nDoor.idChange = -1;
		colDoor.push_back(nDoor);
		if (roomID == 0)
		{
			doorCount++;
			Door nDoor;
			nDoor.col = { SCREEN_WIDTH - DOOR_W * 2 - DOOR_MARGIN, SCREEN_HEIGHT / 2 - DOOR_H, DOOR_W * 2, DOOR_H * 2 };
			nDoor.paint = { SCREEN_WIDTH - DOOR_W * 2 - DOOR_MARGIN, SCREEN_HEIGHT / 2 - DOOR_H, DOOR_W, DOOR_H };
			nDoor.angle = 90.0;
			nDoor.idChange = 1;
			if (iRoomM->getActualLevel() != 1) nDoor.locked = true;
			nDoor.nRoom = GOLDEN;
			colDoor.push_back(nDoor);
		}
	}
	if (doorCount == 1 && (roomID != 0 && roomID != -1 && roomID != -10 && roomID != 1 && roomID != 10 && roomID != -1000))
	{
		roomType = BOSS;
		Door nDoor;
		nDoor.col = { SCREEN_WIDTH / 2 - (int)(156.0f * 0.25f) / 2, SCREEN_HEIGHT / 2 - (int)(149.0f * 0.25f) / 2, (int)(156.0f * 0.25f), (int)(149.0f * 0.25f) };
		nDoor.paint = { nDoor.col.x, nDoor.col.y, 156, 149 };
		nDoor.angle = 0.0;
		nDoor.idChange = 10000;
		colDoor.push_back(nDoor);
		bossMusic = iSoundM->loadAndGetSoundID("Assets/Music/bossMusic.mp3");
	}
	else if (roomID == -1000) roomType = GOLDEN;

}

Room::Room()
{
}

Room::~Room()
{
}
