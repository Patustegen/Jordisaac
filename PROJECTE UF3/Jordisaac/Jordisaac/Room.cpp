#include "Room.h"
#include "Singletons.h"
#include "AttackFly.h"

#define DOOR_MARGIN 30

void Room::init(Player* p)
{
	_player = p;
	if (rID != 0)
	{
		int max = rand() % 3 + 2;
		for (int i = 0; i < max; i++)
		{
			AttackFly* nFly = new AttackFly(rand()%400 + 200, rand()%200 + 200);
			nFly->setPlayer(p);
			enemies.push_back(nFly);
		}
	}
	movCharacters.push_back(_player);
	for (int i = 0; i < enemies.size(); i++)
	{
		movCharacters.push_back(enemies[i]);
	}
}

void Room::update()
{
	if (enemies.size() == 0)
	{
		completed = true;
	}
	_player->update();
	if (completed)
	{
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
		}
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
	}
}

void Room::render()
{
	iVideo->renderGraphic(bg, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
	for (int i = 0; i < colDoor.size(); i++)
	{
		iVideo->renderGraphicEx(oDoor, &colDoor.at(i).col, colDoor.at(i).angle, 2.0f, 2.0f, colDoor.at(i).col.w * completed);
		iVideo->renderGraphicEx(frame, &colDoor.at(i).col, colDoor.at(i).angle, 2.0f, 2.0f);
		for (int i = 0; i < movCharacters.size(); i++)
		{
			movCharacters[i]->render();
		}
	}
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

Room::Room(int nDoors, int roomID)
{
	_player = nullptr;
	completed = false;
	movCharacters.resize(0);
	colDoor.resize(0);
	rID = roomID;
	bg = iResourceM->loadAndGetGraphicID("Assets\\Rooms\\BasementDefault.png");
	oDoor = iResourceM->loadAndGetGraphicID("Assets\\Rooms\\defaultDoor.png");
	cDoor = iResourceM->loadAndGetGraphicID("Assets\\Rooms\\defaultDoor.png");

	frame = iResourceM->loadAndGetGraphicID("Assets\\Characters\\Frame.png");

	enemies.resize(0);
	if (nDoors & 0x01)
	{
		Door nDoor;
		nDoor.col = { SCREEN_WIDTH / 2 - DOOR_W, DOOR_MARGIN, DOOR_W, DOOR_H };
		nDoor.angle = 0.0;
		nDoor.idChange = -10;
		colDoor.push_back(nDoor);
	}
	if (nDoors & 0x02)
	{
		Door nDoor;
		nDoor.col = { SCREEN_WIDTH / 2 - DOOR_W, SCREEN_HEIGHT - DOOR_H * 2 - DOOR_MARGIN, DOOR_W, DOOR_H };
		nDoor.angle = 180.0;
		nDoor.idChange = 10;
		colDoor.push_back(nDoor);
	}
	if (nDoors & 0x04)
	{
		Door nDoor;
		nDoor.col = { SCREEN_WIDTH - DOOR_W * 2 - DOOR_MARGIN, SCREEN_HEIGHT / 2 - DOOR_H, DOOR_W, DOOR_H };
		nDoor.angle = 90.0;
		nDoor.idChange = 1;
		colDoor.push_back(nDoor);
	}
	if (nDoors & 0x08)
	{
		Door nDoor;
		nDoor.col = { DOOR_MARGIN, SCREEN_HEIGHT / 2 - DOOR_H, DOOR_W, DOOR_H };
		nDoor.angle = 270.0;
		nDoor.idChange = -1;
		colDoor.push_back(nDoor);
	}
}

Room::Room()
{
	bg = -1;
	cDoor = -1;
	oDoor = -1;
	completed = false;
	rID = 0;

	frame = -1;
}

Room::~Room()
{
}
