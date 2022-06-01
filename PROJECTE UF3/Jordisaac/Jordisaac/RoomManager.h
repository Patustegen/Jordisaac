#pragma once
#include "Room.h"

struct pos {
	int pY;
	int pX;
};

class RoomManager
{
	static RoomManager* pInstance;
	std::vector<Room> Level;
	int aRoom;
	int aLevel;
	int music;
protected:
	RoomManager();
public:
	static RoomManager* getInstance()
	{
		if (pInstance == NULL) pInstance = new RoomManager();
		return pInstance;
	}
	~RoomManager();
	Room* getActualRoom();
	int getActualLevel() { return aLevel; };
	void changeRoom(int aR, int nMove, Player* p);
	void createNewLevel(int lDiff);
};

