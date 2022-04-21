#include "MainMenu.h"
#include "Singletons.h"

void MainMenu::render()
{
	iVideo->renderGraphic(bgImage, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
	iVideo->renderGraphic(selector, 315 + 5 * menuSelected, 120 + 70 * menuSelected, 33, 36);
}

void MainMenu::update()
{
	if (iInputM->getEvents(ENTER))
	{
		iAudio->playAudio(iSoundM->getSoundByID(sID[2]));
		switch (menuSelected)
		{
		case NEWGAME:
			iSceneD->changeScene(CHARACTER);
			iSceneD->getCurrentScene()->init();
			break;
		case CONTINUE:
			iSceneD->changeScene(GAME);
			break;
		case S_RANKING:
			iSceneD->changeScene(RANK);
			break;
		case S_OPTIONS:
			iSceneD->changeLastScene(OPTIONS);
			break;
		default:
			break;
		}
	}
	else if (iInputM->getEvents(GOUP) || iInputM->getEvents(SHOOTUP))
	{
		iAudio->playAudio(iSoundM->getSoundByID(sID[0]));
		switch (menuSelected)
		{
		case NEWGAME:
			menuSelected = S_OPTIONS;
			break;
		case CONTINUE:
			menuSelected = NEWGAME;
			break;
		case S_RANKING:
			menuSelected = CONTINUE;
			break;
		case S_OPTIONS:
			menuSelected = S_RANKING;
			break;
		default:
			break;
		}
	}
	else if (iInputM->getEvents(GODOWN) || iInputM->getEvents(SHOOTDOWN))
	{
		iAudio->playAudio(iSoundM->getSoundByID(sID[1]));
		switch (menuSelected)
		{
		case NEWGAME:
			menuSelected = CONTINUE;
			break;
		case CONTINUE:
			menuSelected = S_RANKING;
			break;
		case S_RANKING:
			menuSelected = S_OPTIONS;
			break;
		case S_OPTIONS:
			menuSelected = NEWGAME;
			break;
		default:
			break;
		}
	}
	else if (iInputM->getEvents(QUIT))
	{
		SDL_Quit();
	}
}

void MainMenu::load()
{
	bgImage = iResourceM->loadAndGetGraphicID("Assets\\Menus\\mainmenu.png");
	selector = iResourceM->loadAndGetGraphicID("Assets\\Menus\\selector.png");
}

void MainMenu::init()
{
	menuSelected = NEWGAME;
	if (!iAudio->isPlaying(0))
	{
		iAudio->playAudio(iSoundM->getSoundByID(sID[3]), 0,-1);
	}
}

MainMenu::MainMenu()
{
	bgImage = NULL;
	selector = NULL;
	menuSelected = NEWGAME;
}

MainMenu::~MainMenu()
{
}
