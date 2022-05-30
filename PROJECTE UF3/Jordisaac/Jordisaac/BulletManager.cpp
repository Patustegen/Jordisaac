#include "BulletManager.h"
#include "Singletons.h"

BulletManager* BulletManager::pInstance = NULL;

BulletManager::BulletManager()
{
	bullets.resize(0);
}

void BulletManager::AddBullet(float vel, int t, float r, float dmg, Rect* sp, LOOKING coord, DIAGONALS diagonals)
{
	Bullet* nBullet = new Bullet(vel, t, r, dmg, sp, coord, diagonals);
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
		bool touched = false;
		int enemyID = -1;
		bullets[i]->update();
		if (bullets[i]->mustDestroy()) touched = true;

		if (!iRoomM->getActualRoom()->roomWalkable(bullets[i]->getCol())) touched = true;
		if (bullets[i]->getType())
		{
			if (iRoomM->getActualRoom()->enemyCol(bullets[i]->getCol(), &enemyID))
			{
				iRoomM->getActualRoom()->getEnemy(enemyID)->hurt(bullets[i]->getDamage());
				touched = true;
			}
		}
		else
		{
			if (iRoomM->getActualRoom()->playerCol(bullets[i]->getCol()))
			{
				iRoomM->getActualRoom()->getPlayer()->hurt(bullets[i]->getDamage());
				touched = true;
			}
		}
		
		if (touched)
		{
			delete bullets[i];
			bullets.erase(bullets.begin() + i);
			i--;
		}
	}
}

void BulletManager::render()
{
	for (int i = 0; i < bullets.size(); i++) bullets[i]->render();
}
