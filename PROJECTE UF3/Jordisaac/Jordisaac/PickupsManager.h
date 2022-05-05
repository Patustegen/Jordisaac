#pragma once
#include "Pickup.h"
#include <vector>
class PickupsManager
{
	std::vector<Pickup*> pickups;
	static PickupsManager* pInstance;
protected:
	PickupsManager();
public:
	static PickupsManager* getInstance()
	{
		if (pInstance == NULL) pInstance = new PickupsManager();
		return pInstance;
	}
	void AddPickup(int x, int y);
	void init();
	void update();
	void render();
};