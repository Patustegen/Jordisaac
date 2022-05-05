#include "Room.h"
#include "Singletons.h"
#include "AttackFly.h"
#include "Hollow.h"

#define DOOR_MARGIN 30

void Room::init(Player* p)
{
	roomFrame = -1;
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
					nBoss = new Hollow(true);
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
				if (bossType == 0)
				{
					for (int i = 0; i < 4; i++)
					{
						Hollow* nHollowBody = new Hollow();
						nHollowBody->init();
						enemies.push_back(nHollowBody);
					}
					int a = rand() % 360;
					for (int i = 0; i < enemies.size(); i++) enemies[i]->setAngle(a);
				}
			}
			break;
		case GOLDEN:
			break;
		default:
			break;
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
	roomFrame++;
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
		if (roomType == BOSS && bossType == 0 && roomFrame < 30)
		{
			for (int i = 0; i < roomFrame; i++)
			{
				if (roomFrame % 6 == 0)
				{
					enemies[i / 6]->update();
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
		}
	}
}

void Room::render()
{
	iVideo->renderGraphic(bg, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
	for (int i = 0; i < colDoor.size(); i++)
	{
		iVideo->renderGraphicEx(gDoor, &colDoor.at(i).paint, colDoor.at(i).angle, 2.0f, 2.0f, colDoor.at(i).paint.w * completed);
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

Room::Room(int nDoors, int roomID)
{
	bossType = -1;
	roomFrame = 0;
	int doorCount = 0;
	roomType = NORMAL;
	_player = nullptr;
	completed = false;
	movCharacters.resize(0);
	colDoor.resize(0);
	rID = roomID;
	bg = iResourceM->loadAndGetGraphicID("Assets\\Rooms\\BasementDefault.png");
	gDoor = iResourceM->loadAndGetGraphicID("Assets\\Rooms\\defaultDoor.png");


	enemies.resize(0);
	if (nDoors & 0x01)
	{
		doorCount++;
		Door nDoor;
		nDoor.col = { SCREEN_WIDTH / 2 - DOOR_W, DOOR_MARGIN, DOOR_W * 2, DOOR_H * 2 };
		nDoor.paint = { SCREEN_WIDTH / 2 - DOOR_W, DOOR_MARGIN, DOOR_W, DOOR_H };
		nDoor.angle = 0.0;
		nDoor.idChange = -10;
		colDoor.push_back(nDoor);
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
	}
	if (doorCount == 1 /* && roomID != 0*/)
	{
		roomType = BOSS;
	}
}

Room::Room()
{
	_player = nullptr;
	bg = -1;
	gDoor = -1;
	completed = false;
	rID = 0;
	roomType = NORMAL;
}

Room::~Room()
{
}
