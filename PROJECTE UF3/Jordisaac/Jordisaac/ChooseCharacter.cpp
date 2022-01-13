#include "ChooseCharacter.h"
#include "Singletons.h"
#define CHAR_W 67
#define CHAR_H 90

void ChooseCharacter::render()
{
	iResourceM->setAlphaGraphic(bgImage, alpha);
	iResourceM->setAlphaGraphic(characs, alpha);
	iVideo->renderGraphic(bgImage, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
	iVideo->renderGraphic(characs, SCREEN_WIDTH / 2 - CHAR_W * 2, SCREEN_HEIGHT / 2 - CHAR_H / 2 - 50, CHAR_W, CHAR_H, CHAR_W * bCharacter, 0, 0.75, 0.75);
	iVideo->renderGraphic(characs, SCREEN_WIDTH / 2 + CHAR_W, SCREEN_HEIGHT / 2 - CHAR_H / 2 - 50, CHAR_W, CHAR_H, CHAR_W * nCharacter, 0, 0.75, 0.75);
	iVideo->renderGraphic(characs, SCREEN_WIDTH / 2 - CHAR_W / 2, SCREEN_HEIGHT / 2 - CHAR_H / 2 - 50, CHAR_W, CHAR_H, CHAR_W * aCharacter);
}

void ChooseCharacter::update()
{
	if (!selected)
	{
		for (int i = 0; i < iInputM->getEvents().size(); i++)
		{
			if (iInputM->getEvents()[i] == ENTER)
			{
				selected = true;
				iAudio->haltChannel();
				iAudio->playAudio(iSoundM->getSoundByID(audio),0);
			}
			else if (iInputM->getEvents()[i] == GOLEFT || iInputM->getEvents()[i] == SHOOTLEFT)
			{
				switch (aCharacter)
				{
				case ISAAC:
					nCharacter = aCharacter;
					aCharacter = bCharacter;
					bCharacter = CAIN;
					break;
				case MAGDALENE:
					nCharacter = aCharacter;
					aCharacter = bCharacter;
					bCharacter = SAMSON;
					break;
				case CAIN:
					nCharacter = aCharacter;
					aCharacter = bCharacter;
					bCharacter = ISAAC;
					break;
				case SAMSON:
					nCharacter = aCharacter;
					aCharacter = bCharacter;
					bCharacter = MAGDALENE;
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
					bCharacter = aCharacter;
					aCharacter = nCharacter;
					nCharacter = CAIN;
					break;
				case MAGDALENE:
					bCharacter = aCharacter;
					aCharacter = nCharacter;
					nCharacter = SAMSON;
					break;
				case CAIN:
					bCharacter = aCharacter;
					aCharacter = nCharacter;
					nCharacter = ISAAC;
					break;
				case SAMSON:
					bCharacter = aCharacter;
					aCharacter = nCharacter;
					nCharacter = MAGDALENE;
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
	else
	{
		if (iAudio->isPlaying(0))
		{
			if (alpha > 0)
			{
				alpha -= 4;

			}
			if (alpha < 0)
			{
				alpha = 0;
			}
		}
		else
		{
			iSceneD->setSelectedCharacter(aCharacter);
			iSceneD->changeScene(GAME);
			iSceneD->getCurrentScene()->init();
		}
	}
}

void ChooseCharacter::load()
{
	bgImage = iResourceM->loadAndGetGraphicID("Assets\\Menus\\whoami.png");
	characs = iResourceM->loadAndGetGraphicID("Assets\\Characters\\Choose.png");
	audio = iSoundM->loadAndGetSoundID("Assets\\Music\\game-start.mp3");
}

void ChooseCharacter::init()
{
	aCharacter = ISAAC;
	bCharacter = SAMSON;
	nCharacter = MAGDALENE;
	selected = false;
	alpha = 255;
}

ChooseCharacter::ChooseCharacter()
{
	aCharacter = ISAAC;
	bCharacter = SAMSON;
	nCharacter = MAGDALENE;
	selected = false;
	bgImage = -1;
	characs = -1;
	audio = -1;
}
