#include "Room.h"

void Room::init()
{
}

void Room::update()
{
}

void Room::render()
{
}

Room::Room()
{
	completed = false;
	doors = 0;
	rID = -1;
	bg = -1;
	enemies.resize(0);
}

Room::~Room()
{
}
