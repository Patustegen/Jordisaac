#include "Ranking.h"
#include "Singletons.h"

void Ranking::render()
{
}

void Ranking::update()
{
	if (iInputM->getEvents(QUIT))
	{
		iSceneD->changeScene(MAIN);
	}
}

void Ranking::load()
{
}
