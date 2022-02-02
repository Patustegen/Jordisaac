#include "RoomManager.h"
#include <algorithm>
#include <stdlib.h>     
#include <time.h> 
#include <math.h>

RoomManager* RoomManager::pInstance = NULL;

using namespace std;

RoomManager::RoomManager()
{
	Level.resize(0);
	aRoom = 0;
	srand((unsigned int)time(NULL));
}

void RoomManager::createNewLevel(int lDiff)
{
	int maxRooms = min(20, (int)(rand() + 5 + floor(lDiff * 10 / 3)));
}
