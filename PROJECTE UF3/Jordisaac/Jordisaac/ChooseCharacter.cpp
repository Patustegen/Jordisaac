#include "ChooseCharacter.h"
#include "Singletons.h"

void ChooseCharacter::render()
{
	iVideo->renderGraphic(bgImage, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
}

void ChooseCharacter::update()
{
	for (int i = 0; i < iInputM->getEvents().size(); i++)
	{
		if (iInputM->getEvents()[i] == ENTER)
		{
			iSceneD->setSelectedCharacter(aCharacter);
			iSceneD->changeScene(GAME);
			iSceneD->getCurrentScene()->init();
		}
		else if (iInputM->getEvents()[i] == GOLEFT || iInputM->getEvents()[i] == SHOOTLEFT)
		{
			switch (aCharacter)
			{
			case ISAAC:
				aCharacter = SAMSON;
				break;
			case MAGDALENE:
				aCharacter = ISAAC;
				break;
			case CAIN:
				aCharacter = MAGDALENE;
				break;
			case SAMSON:
				aCharacter = CAIN;
				break;
			default:
				break;
			}
		}
		else if (iInputM->getEvents()[i] == GORIGHT || iInputM->getEvents()[i] == SHOOTRIGHT)
		{
			switch (aCharacter)
			{
			case ISAAC:
				aCharacter = MAGDALENE;
				break;
			case MAGDALENE:
				aCharacter = CAIN;
				break;
			case CAIN:
				aCharacter = SAMSON;
				break;
			case SAMSON:
				aCharacter = ISAAC;
				break;
			default:
				break;
			}
		}
		else if (iInputM->getEvents()[i] == QUIT)
		{
			iSceneD->changeScene(MAIN);
		}
	}
}

void ChooseCharacter::load()
{
	bgImage = iResourceM->loadAndGetGraphicID("Assets\\Menus\\whoami.png");
}

void ChooseCharacter::init()
{
}
