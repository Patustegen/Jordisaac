#include "Game.h"
#include "Singletons.h"

void Game::render()
{
	player->render();
}

void Game::update()
{
	if (iInputM->getEvents(QUIT)) 
	{
		iSceneD->changeScene(PAUSE);
	}
	player->update();
}

void Game::load()
{

}

void Game::init()
{
	iInputM->switchGameMode(true);
	player = new Player();
}
