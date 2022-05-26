#pragma once
#include <vector>
#include "Enemy.h"
#include "Player.h"

#define DOOR_W 61
#define DOOR_H 39
#define ROOM_MARGIN_Y 90
#define ROOM_MARGIN_X 105

enum ROOM_TYPE { NORMAL, BOSS, GOLDEN };

struct Door
{
	Rect col;
	Rect paint;
	double angle;
	int idChange;
	bool locked = false;
	ROOM_TYPE nRoom = NORMAL;
};

class Room
{
private:
	bool completed;
	int rID;
	Player* _player;
	ROOM_TYPE roomType;
	std::vector<Enemy*> enemies;
	std::vector<BaseCharacter*> movCharacters;
	std::vector<Door> colDoor;
	int bg;
	int gDoor;
	int bossType;
public:
	void init(Player* p);
	void update();
	void render();
	bool roomWalkable(Rect* col);
	bool colWalkable(Rect* col);
	int getRoomID() { return rID; };
	ROOM_TYPE getRoomType() { return roomType; };
	bool enemyCol(Rect* col, int* enemyID = nullptr);
	Enemy* getEnemy(int enemyID) { return enemies[enemyID]; };
	bool playerCol(Rect* col);
	std::vector<Door> getDoorVect() { return colDoor; };
	void setDoorFrame(int i, ROOM_TYPE nR) { colDoor[i].nRoom = nR; };
	void damageAll();
	Room(int nDoors, int roomID);
	Room();
	~Room();
};

