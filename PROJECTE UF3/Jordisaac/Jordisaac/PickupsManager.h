#pragma once
#include "Pickup.h"
#include <vector>
#include "Player.h"
class PickupsManager
{
	std::vector<Pickup*> pickups;
	static PickupsManager* pInstance;
	int pills[6];
	int sID[12];
	Player* _p;
protected:
	PickupsManager();
public:
	static PickupsManager* getInstance()
	{
		if (pInstance == NULL) pInstance = new PickupsManager();
		return pInstance;
	}
	void setPlayer(Player* p) { _p = p; };
	void AddPickup(int x, int y, PICKUP_TYPE t, int i = -1);
	void init();
	void update();
	void render();
};