#include "OptionsMenu.h"
#include "Singletons.h"

void OptionsMenu::render()
{
	
}

void OptionsMenu::update()
{
	if (iInputM->getEvents(QUIT))
	{
		iSceneD->changeScene(iSceneD->getLastSceneEnum());
	}
	else if (iInputM->getEvents(GOUP) || iInputM->getEvents(SHOOTUP))
	{
		switch (selected)
		{
		case CONTROLS:
			selected = GAMMA;
			break;
		case SFX:
			selected = CONTROLS;
			break;
		case MUSIC:
			selected = SFX;
			break;
		case GAMMA:
			selected = MUSIC;
			break;
		default:
			break;
		}
	}
	else if (iInputM->getEvents(GODOWN) || iInputM->getEvents(SHOOTDOWN))
	{
		switch (selected)
		{
		case CONTROLS:
			selected = SFX;
			break;
		case SFX:
			selected = MUSIC;
			break;
		case MUSIC:
			selected = GAMMA;
			break;
		case GAMMA:
			selected = CONTROLS;
			break;
		default:
			break;
		}
	}
	else if (iInputM->getEvents(ENTER))
	{
		switch (selected)
		{
		case CONTROLS:
			break;
		case SFX:
			break;
		case MUSIC:
			break;
		case GAMMA:
			break;
		default:
			break;
		}
	}
}

void OptionsMenu::load()
{
}
