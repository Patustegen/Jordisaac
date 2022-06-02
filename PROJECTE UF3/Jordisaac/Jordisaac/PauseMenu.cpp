#include "PauseMenu.h"
#include "Singletons.h"

void PauseMenu::render()
{
	iResourceM->setAlphaGraphic(bgImage, 100);
	iVideo->renderGraphic(bgImage, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
	iVideo->renderGraphic(gPaused, SCREEN_WIDTH / 2 - 489 / 2, SCREEN_HEIGHT / 2 - 422 / 2, 489, 422);
	iVideo->renderGraphic(gSelector, 350, 310 + 52 * selected, 33, 36);
}

void PauseMenu::update()
{
	if (iInputM->getEvents(QUIT))
	{
		iSceneD->changeScene(GAME);
		iInputM->switchGameMode(true);
	}
	else if (iInputM->getEvents(GOUP) || iInputM->getEvents(SHOOTUP))
	{
		iAudio->playAudio(iSoundM->getSoundByID(sID[0]));
		switch (selected)
		{
		case P_OPTIONS:
			selected = EXIT;
			break;
		case RESUME:
			selected = P_OPTIONS;
			break;
		case EXIT:
			selected = RESUME;
			break;
		default:
			break;
		}
	}
	else if (iInputM->getEvents(GODOWN) || iInputM->getEvents(SHOOTDOWN))
	{
		iAudio->playAudio(iSoundM->getSoundByID(sID[1]));
		switch (selected)
		{
		case P_OPTIONS:
			selected = RESUME;
			break;
		case RESUME:
			selected = EXIT;
			break;
		case EXIT:
			selected = P_OPTIONS;
			break;
		default:
			break;
		}
	}
	else if (iInputM->getEvents(ENTER))
	{
		switch (selected)
		{
		case P_OPTIONS:
			iSceneD->changeLastScene(OPTIONS);
			iSceneD->getCurrentScene()->init();
			break;
		case RESUME:
			iSceneD->changeScene(GAME);
			iInputM->switchGameMode(true);
			break;
		case EXIT:
			iAudio->haltChannel();
			iSceneD->changeScene(MAIN);
			iSceneD->getCurrentScene()->init();
			break;
		default:
			break;
		}
	}
}

void PauseMenu::load()
{
}

void PauseMenu::init()
{
	selected = P_OPTIONS;
	iInputM->switchGameMode(false);
	bgImage = iResourceM->loadAndGetGraphicID("Assets/Menus/screenshot.bmp", true);
	gSelector = iResourceM->loadAndGetGraphicID("Assets/Menus/selector.png");
	gPaused = iResourceM->loadAndGetGraphicID("Assets/Menus/paused.png");
}
