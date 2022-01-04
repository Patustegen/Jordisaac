#include "Portada.h"
#include "Singletons.h"


void Portada::render()
{
	iResourceM->setAlphaGraphic(bgImage, alpha);
	iVideo->renderGraphic(bgImage, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
}

void Portada::update()
{
	if (alpha < 255)
	{
		if (alpha > 150)
		{
			alpha += 7;
		}
		else
		{
			alpha += 2;
		}
	}
	if (alpha > 255)
	{
		alpha = 255;
	}
	for (int i = 0; i < iInputM->getEvents().size(); i++)
	{
		if (iInputM->getEvents()[i] == ENTER)
		{
			iSceneD->changeScene(MAIN);
		}
	}
}

void Portada::load()
{
	bgImage = iResourceM->loadAndGetGraphicID("Assets\\Menus\\splashmenu.png");
	bgMusic = iSoundM->loadAndGetSoundID("Assets\\Music\\intro-theme.mp3");
	alpha = 0;
}

void Portada::init()
{
	iAudio->playAudio(iSoundM->getSoundByID(bgMusic), 0, -1);
}
