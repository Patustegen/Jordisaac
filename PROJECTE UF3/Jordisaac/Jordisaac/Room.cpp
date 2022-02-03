#include "Room.h"
#include "Singletons.h"

#define DOOR_MARGIN 23

void Room::init()
{
}

void Room::update()
{
	if (enemies.size() == 0)
	{
		completed = true;
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
		}
		else
		{
			iVideo->renderGraphicEx(cDoor, &colDoor.at(i).col, colDoor.at(i).angle, 2.0f, 2.0f);
		}
	}
}

bool Room::roomWalkable(Rect* col)
{
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
	enemies.resize(0);
	if (nDoors & 0x01)
	{
		Door nDoor;
		nDoor.col = { SCREEN_WIDTH / 2 - DOOR_W, DOOR_MARGIN, DOOR_W, DOOR_H };
		nDoor.angle = 0.0;
		colDoor.push_back(nDoor);
	}
	if (nDoors & 0x02)
	{
		Door nDoor;
		nDoor.col = { SCREEN_WIDTH / 2 - DOOR_W, SCREEN_HEIGHT - DOOR_H * 2 - DOOR_MARGIN, DOOR_W, DOOR_H };
		nDoor.angle = 180.0;
		colDoor.push_back(nDoor);
	}
	if (nDoors & 0x04)
	{
		Door nDoor;
		nDoor.col = { SCREEN_WIDTH - DOOR_W * 2 - DOOR_MARGIN, SCREEN_HEIGHT / 2 - DOOR_H, DOOR_W, DOOR_H };
		nDoor.angle = 90.0;
		colDoor.push_back(nDoor);
	}
	if (nDoors & 0x08)
	{
		Door nDoor;
		nDoor.col = { 0, SCREEN_HEIGHT / 2 - DOOR_H - DOOR_MARGIN, DOOR_W, DOOR_H };
		nDoor.angle = 270.0;
		colDoor.push_back(nDoor);
	}
}

Room::~Room()
{
}
