#include "BulletManager.h"
#include "Singletons.h"

BulletManager* BulletManager::pInstance = NULL;

BulletManager::BulletManager()
{
	bullets.resize(0);
}

void BulletManager::AddBullet(float vel, int t, Rect* sp, LOOKING coord, DIAGONALS diagonals)
{
	Bullet* nBullet = new Bullet(vel, t, sp, coord, diagonals);
	bullets.push_back(nBullet);
}

void BulletManager::init()
{
	for (int i = 0; i < bullets.size(); i++)
	{
		delete bullets[i];
		bullets.erase(bullets.begin() + i);
		i--;
	}
	bullets.resize(0);
}

void BulletManager::update()
{
	for (int i = 0; i < bullets.size(); i++)
	{
		bullets[i]->update();
		if (!iRoomM->getActualRoom()->roomWalkable(bullets[i]->getCol()))
		{
			delete bullets[i];
			bullets.erase(bullets.begin() + i);
			i--;
		}
	}
}

void BulletManager::render()
{
	for (int i = 0; i < bullets.size(); i++)
	{
		bullets[i]->render();
	}
}
