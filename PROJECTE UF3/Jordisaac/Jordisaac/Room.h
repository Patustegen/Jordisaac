#pragma once
#include <vector>
#include "Enemy.h"

#define DOOR_W 49
#define DOOR_H 33
#define ROOM_MARGIN_Y 90
#define ROOM_MARGIN_X 105

struct Door
{
	Rect col;
	double angle;
};

class Room
{
private:
	bool completed;
	int rID;
	std::vector<Enemy*> enemies;
	std::vector<Door> colDoor;
	int bg;
	int oDoor;
	int cDoor;
public:
	void init();
	void update();
	void render();
	bool roomWalkable(Rect* col);
	Room(int nDoors, int roomID);
	~Room();
};

