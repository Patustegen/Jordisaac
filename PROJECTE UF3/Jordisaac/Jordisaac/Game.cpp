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
	iVideo->renderGraphic(bg, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
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
}

void Game::load()
{
	ui->load();
	bg = iResourceM->loadAndGetGraphicID("Assets\\Rooms\\BasementDefault.png");
}

void Game::init()
{
	iInputM->switchGameMode(true);
	ui->setPlayer(player);
	player->init();
	ui->init();
}
