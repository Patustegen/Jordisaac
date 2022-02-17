#include "Game.h"
#include "Singletons.h"

Game::Game()
{
	bg = -1;
	player = new Player();
	ui = new UI();
}

void Game::render()
{
	iRoomM->getActualRoom()->render();
	player->render();
	ui->render();
}

void Game::update()
{
	if (iInputM->getEvents(QUIT)) 
	{
		iSceneD->changeScene(PAUSE);
		iSceneD->getCurrentScene()->init();
	}
	player->update();
	iRoomM->getActualRoom()->update(player->getCol());
}

void Game::load()
{
	ui->load();
	bg = iResourceM->loadAndGetGraphicID("Assets\\Rooms\\BasementDefault.png");
}

void Game::init()
{
	iRoomM->createNewLevel(1);
	iInputM->switchGameMode(true);
	ui->setPlayer(player);
	player->init();
	ui->init();
}
