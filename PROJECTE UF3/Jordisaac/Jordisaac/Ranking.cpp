#include "Ranking.h"
#include "Singletons.h"

void Ranking::render()
{
}

void Ranking::update()
{
	for (int i = 0; i < iInputM->getEvents().size(); i++)
	{
		if (iInputM->getEvents()[i] == QUIT)
		{
			iSceneD->changeScene(MAIN);
		}
	}
}

void Ranking::load()
{
}
