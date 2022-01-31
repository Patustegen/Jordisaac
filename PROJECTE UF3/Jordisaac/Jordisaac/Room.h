#pragma once
#include <vector>
#include "Enemy.h"

class Room
{
private:
	bool completed;
	int doors;
	int rID;
	std::vector<Enemy*> enemies;
	int bg;
public:
	void init();
	void update();
	void render();
	Room();
	~Room();
};

