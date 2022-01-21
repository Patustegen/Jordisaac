#include "Game.h"
#include "Singletons.h"

Game::Game()
{
	player = new Player();
	ui = new UI();
}

void Game::render()
{
	player->render();
	ui->render();
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
	ui->load();
}

void Game::init()
{
	iInputM->switchGameMode(true);
	ui->setPlayer(player);
	player->init();
	ui->init();
}
