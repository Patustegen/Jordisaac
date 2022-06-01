#pragma once
#include "Bullet.h"
#include <vector>
#include "enums.h"
class BulletManager
{
	std::vector<Bullet*> bullets;
	static BulletManager* pInstance;
protected:
	BulletManager();
public:
	static BulletManager* getInstance()
	{
		if (pInstance == NULL) pInstance = new BulletManager();
		return pInstance;
	}
	void AddBullet(float vel, int t, float r, float dmg, Rect* sp, LOOKING coord, int a);
	bool preciseCollision(Rect* col, int t);
	void init();
	void update();
	void render();
};

