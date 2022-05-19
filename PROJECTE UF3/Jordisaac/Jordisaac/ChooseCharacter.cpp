#include "ChooseCharacter.h"
#include "Singletons.h"
#define CHAR_W 67
#define CHAR_H 90
#define STAT_W 248
#define STAT_H 165

void ChooseCharacter::render()
{
	iResourceM->setAlphaGraphic(bgImage, alpha);
	iResourceM->setAlphaGraphic(characs, alpha);
	iResourceM->setAlphaGraphic(gStats[aCharacter], alpha);
	iVideo->renderGraphic(bgImage, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
	iVideo->renderGraphic(characs, SCREEN_WIDTH / 2 - CHAR_W * 2, SCREEN_HEIGHT / 2 - CHAR_H / 2 - 50, CHAR_W, CHAR_H, CHAR_W * bCharacter, 0, 0.75, 0.75);
	iVideo->renderGraphic(characs, SCREEN_WIDTH / 2 + CHAR_W, SCREEN_HEIGHT / 2 - CHAR_H / 2 - 50, CHAR_W, CHAR_H, CHAR_W * nCharacter, 0, 0.75, 0.75);
	iVideo->renderGraphic(characs, SCREEN_WIDTH / 2 - CHAR_W / 2, SCREEN_HEIGHT / 2 - CHAR_H / 2 - 50, CHAR_W, CHAR_H, CHAR_W * aCharacter);
	iVideo->renderGraphic(gStats[aCharacter], SCREEN_WIDTH / 2 - STAT_W / 2, SCREEN_HEIGHT / 2, STAT_W, STAT_H);
}

void ChooseCharacter::update()
{
	if (!selected)
	{
		if (iInputM->getEvents(ENTER))
		{
			selected = true;
			iAudio->haltChannel();
			iAudio->playAudio(iSoundM->getSoundByID(audio),0);
		}
		else if (iInputM->getEvents(GOLEFT) || iInputM->getEvents(SHOOTLEFT))
		{
			iAudio->playAudio(iSoundM->getSoundByID(sID[1]));
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
		else if (iInputM->getEvents(GORIGHT) || iInputM->getEvents(SHOOTRIGHT))
		{
			iAudio->playAudio(iSoundM->getSoundByID(sID[0]));
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
		else if (iInputM->getEvents(QUIT))
		{
			iAudio->playAudio(iSoundM->getSoundByID(sID[2]));
			iSceneD->changeScene(MAIN);
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
			iSceneD->getCurrentScene()->load();
			iSceneD->getCurrentScene()->init();
		}
	}
}

void ChooseCharacter::load()
{
	bgImage = iResourceM->loadAndGetGraphicID("Assets\\Menus\\whoami.png");
	characs = iResourceM->loadAndGetGraphicID("Assets\\Characters\\Choose.png");
	audio = iSoundM->loadAndGetSoundID("Assets\\Music\\game-start.mp3");
	gStats[ISAAC] = iResourceM->loadAndGetGraphicID("Assets\\Characters\\Stats_Isaac.webp");
	gStats[MAGDALENE] = iResourceM->loadAndGetGraphicID("Assets\\Characters\\Stats_Magdalene.webp");
	gStats[SAMSON] = iResourceM->loadAndGetGraphicID("Assets\\Characters\\Stats_Samson.webp");
	gStats[CAIN] = iResourceM->loadAndGetGraphicID("Assets\\Characters\\Stats_Cain.webp");
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
	for (int i = 0; i < 4; i++) gStats[i] = -1;
}
