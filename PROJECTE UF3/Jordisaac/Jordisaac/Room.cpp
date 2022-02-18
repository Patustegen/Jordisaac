#include "Room.h"
#include "Singletons.h"
#include "AttackFly.h"

#define DOOR_MARGIN 30

void Room::init()
{
	AttackFly* nFly = new AttackFly(450,250);
	enemies.push_back(nFly);
}

void Room::update(Rect* pCol)
{
	if (enemies.size() == 0)
	{
		completed = true;
	}
	else
	{
		Enemy::setPPos(pCol);
		for (int i = 0; i < enemies.size(); i++)
		{
			enemies[i]->update();
		}
	}

	if (completed)
	{
		for (int i = 0; i < colDoor.size(); i++)
		{
			if (iVideo->isInside(&colDoor[i].col,pCol))
			{
				iRoomM->changeRoom(rID,colDoor[i].idChange, pCol);
			}
		}
	}
	else
	{

	}
}

void Room::render()
{
	iVideo->renderGraphic(bg, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
	for (int i = 0; i < colDoor.size(); i++)
	{
		if (completed)
		{
			iVideo->renderGraphicEx(oDoor, &colDoor.at(i).col, colDoor.at(i).angle, 2.0f, 2.0f);
			iVideo->renderGraphicEx(frame, &colDoor.at(i).col, colDoor.at(i).angle, 2.0f, 2.0f);
		}
		else
		{
			iVideo->renderGraphicEx(cDoor, &colDoor.at(i).col, colDoor.at(i).angle, 2.0f, 2.0f);
		}
		for (int i = 0; i < enemies.size(); i++)
		{
			enemies[i]->render();
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
	completed = false;
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
		nDoor.idChange = -1;
		colDoor.push_back(nDoor);
	}
	if (nDoors & 0x08)
	{
		Door nDoor;
		nDoor.col = { DOOR_MARGIN, SCREEN_HEIGHT / 2 - DOOR_H, DOOR_W, DOOR_H };
		nDoor.angle = 270.0;
		nDoor.idChange = 1;
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
