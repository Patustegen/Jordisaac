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
	if (iInputM->getEvents(ENTER))
	{
		iSceneD->changeScene(MAIN);
		iAudio->playAudio(iSoundM->getSoundByID(sID[2]));
	}
}

void Portada::load()
{
	bgImage = iResourceM->loadAndGetGraphicID("Assets\\Menus\\splashmenu.png");
}

void Portada::init()
{
	iAudio->playAudio(iSoundM->getSoundByID(sID[3]), 0, -1);
	alpha = 0;
}
