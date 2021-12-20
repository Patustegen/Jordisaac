#include "Game.h"
#include "Singletons.h"

void Game::render()
{
}

void Game::update()
{
	for (int i = 0; i < iInputM->getEvents().size(); i++)
	{
		if (iInputM->getEvents()[i] == QUIT)
		{
			iSceneD->changeScene(PAUSE);
		}
	}
}

void Game::load()
{
}
