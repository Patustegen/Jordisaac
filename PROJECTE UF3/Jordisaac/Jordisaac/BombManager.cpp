#include "BombManager.h"

BombManager* BombManager::pInstance = NULL;

BombManager::BombManager()
{
	bombs.resize(0);
}

void BombManager::AddBomb(int x, int y)
{
	Bomb* nBomb = new Bomb(x, y);
	bombs.push_back(nBomb);
}

void BombManager::init()
{
	for (int i = 0; i < bombs.size(); i++)
	{
		delete bombs[i];
		bombs.erase(bombs.begin() + i);
		i--;
	}
	bombs.resize(0);
}

void BombManager::update()
{
	for (int i = 0; i < bombs.size(); i++)
	{
		bombs[i]->update();
		if (bombs[i]->mustDestroy())
		{
			delete bombs[i];
			bombs.erase(bombs.begin() + i);
			i--;
		}
	}
}

void BombManager::render()
{
	for (int i = 0; i < bombs.size(); i++) bombs[i]->render();
}
