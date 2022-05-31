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
				int max = rand() % 3 + 2;
				for (int i = 0; i < max; i++)
				{
					AttackFly* nFly = new AttackFly(rand()%400 + 200, rand()%200 + 200);
					nFly->setPlayer(p);
					enemies.push_back(nFly);
				}
				Pooter* nPoot = new Pooter(rand()%400 + 200, rand()%200 + 200);
				nPoot->setPlayer(p);
				enemies.push_back(nPoot);
			}
			break;
		case BOSS:
			if (!completed)
			{
				bossType = rand() % 3;
				bossType = 0;
				Boss* nBoss = nullptr;
				switch (bossType)
				{
				case 0:
					Hollow * nHollow = new Hollow();
					for (int i = 0; i < nHollow->getHBody().size(); i++) enemies.push_back(nHollow->getHBody()[i]);
					nBoss = nHollow;
					break;
				case 1:
					break;
				case 2:
					break;
				default:
					break;
				}
				nBoss->init();
				enemies.push_back(nBoss);
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
			for (int i = 0; i < 13; i++)
			{
				if (i < 6)
				{
					iPickM->AddPickup(ROOM_MARGIN_X + i * 35, ROOM_MARGIN_Y + 10, NORMAL_PU, i);
				}
				else
				{
					iPickM->AddPickup(ROOM_MARGIN_X + i * 35, ROOM_MARGIN_Y + 60, NORMAL_PU, i);
				}
			}
			for (int i = 0; i < 6; i++)
			{
				iPickM->AddPickup(ROOM_MARGIN_X + i * 35, SCREEN_HEIGHT - ROOM_MARGIN_Y - 60, CONS_PU, i);
			}
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
		for (int i = 0; i < enemies.size(); i++)
		{
			enemies[i]->update();
			if (iVideo->onCollision(_player->getCol(), enemies[i]->getCol())) _player->getHurt();
			if (enemies[i]->getHP() <= 0)
			{
				delete enemies[i];
				enemies.erase(enemies.begin() + i);
				i--;
			}
		}

		bool swapped = false;
		movCharacters.resize(0);
		movCharacters.push_back(_player);
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
		if (enemies.size() == 0)
		{
			completed = true;
			movCharacters.resize(0);
			movCharacters.push_back(_player);
			int max = rand() % 2 + (_player->getStat(LUCK) / 2);
			for (int i = 0; i < max; i++)
			{
				iPickM->AddPickup((SCREEN_WIDTH / 2) - (rand() % 15 - 10), (SCREEN_HEIGHT/ 2) - (rand() % 15 - 10), NORMAL_PU);
			}
		}
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
		iVideo->renderGraphicEx(gDoor, &colDoor.at(0).paint, colDoor.at(0).angle, 2.0f, 2.0f, colDoor.at(0).paint.w * completed, colDoor.at(0).paint.h);
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
	int doorCount = 0;
	roomType = NORMAL;
	_player = nullptr;
	completed = false;
	movCharacters.resize(0);
	colDoor.resize(0);
	enemies.resize(0);
	rID = roomID;
	bg = iResourceM->loadAndGetGraphicID("Assets\\Rooms\\BasementDefault.png");
	gDoor = iResourceM->loadAndGetGraphicID("Assets\\Rooms\\doorsImages.png");


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
	if (doorCount == 1  && (roomID != 0 && roomID != -1 && roomID != -10 && roomID != 1 && roomID != 10)) roomType = BOSS;
	else if (doorCount == 1 && (roomID == -1 || roomID == -10 || roomID == 1 || roomID == 10)) roomType = GOLDEN;
}

Room::Room()
{
}

Room::~Room()
{
}
