#include "Game.h"
#include "Singletons.h"

Game::Game()
{
	bgImage[0] = -1;
	bgImage[1] = -1;
	bgImage[2] = -1;
	player = new Player();
	ui = new UI();
}

void Game::render()
{
	iRoomM->getActualRoom()->render();
	ui->render();
}

void Game::update()
{
	if (iInputM->getEvents(QUIT)) 
	{
		iVideo->saveScreenshot();
		iSceneD->changeScene(PAUSE);
		iSceneD->getCurrentScene()->init();
	}
	iRoomM->getActualRoom()->update();
}

void Game::load()
{
	ui->load();
	bgImage[0] = iResourceM->loadAndGetGraphicID("Assets\\Rooms\\BasementDefault.png");
	bgImage[1] = iResourceM->loadAndGetGraphicID("Assets\\Rooms\\CavesDefault.png");
	bgImage[2] = iResourceM->loadAndGetGraphicID("Assets\\Rooms\\DepthsDefault.png");
}

void Game::init()
{
	iRoomM->createNewLevel(1);
	iInputM->switchGameMode(true);
	iPickM->setPlayer(player);
	ui->setPlayer(player);
	player->init();
	ui->init();
	iPickM->init();
	iBombM->init();
	iBulletM->init();
	iRoomM->getActualRoom()->init(player);
}
