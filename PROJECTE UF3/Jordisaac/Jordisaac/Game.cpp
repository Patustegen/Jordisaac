#include "Game.h"
#include "Singletons.h"

void Game::render()
{
	player->render();
}

void Game::update()
{
	player->update();
}

void Game::load()
{

}

void Game::init()
{
	player = new Player();
}
