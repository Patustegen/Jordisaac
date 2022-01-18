#include "PauseMenu.h"
#include "Singletons.h"

void PauseMenu::render()
{

}

void PauseMenu::update()
{
	if (iInputM->getEvents(QUIT))
	{
		iSceneD->changeScene(GAME);
	}
	else if (iInputM->getEvents(GOUP) || iInputM->getEvents(SHOOTUP))
	{
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
			break;
		case RESUME:
			iSceneD->changeScene(GAME);
			break;
		case EXIT:
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
}
