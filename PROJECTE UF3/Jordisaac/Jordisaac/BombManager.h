#pragma once
#include "Bomb.h"
#include <vector>
#include "enums.h"
class BombManager
{
	std::vector<Bomb*> bombs;
	static BombManager* pInstance;
protected:
	BombManager();
public:
	static BombManager* getInstance()
	{
		if (pInstance == NULL) pInstance = new BombManager();
		return pInstance;
	}
	void AddBomb(int x, int y);
	void init();
	void update();
	void render();
};

