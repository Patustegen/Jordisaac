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
	int idChange;
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


	int frame;
public:
	void init();
	void update(Rect* pCol);
	void render();
	bool roomWalkable(Rect* col);
	int getRoomID() { return rID; };
	std::vector<Door> getDoorVect() { return colDoor; };
	Room(int nDoors, int roomID);
	Room();
	~Room();
};

