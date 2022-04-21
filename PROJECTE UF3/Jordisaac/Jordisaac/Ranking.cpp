#include "Ranking.h"
#include "Singletons.h"

void Ranking::render()
{
}

void Ranking::update()
{
	if (iInputM->getEvents(QUIT))
	{
		iAudio->playAudio(iSoundM->getSoundByID(sID[2]));
		iSceneD->changeScene(MAIN);
	}
}

void Ranking::load()
{
}
