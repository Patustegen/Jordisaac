#include "GameOver.h"
#include "Singletons.h"
#include "fstream"

using namespace std;

void GameOver::render()
{
}

void GameOver::update()
{
	if (iInputM->getEvents(QUIT))
	{
		iSceneD->changeScene(MAIN);
		iSceneD->getCurrentScene()->init();
	}
}

void GameOver::load()
{
}

void GameOver::init(int s)
{
	fstream file("rank.data", ios::out | ios::binary);
	if (file.is_open())
	{
		int c = iSceneD->getSelectedCharacter();
		file.write((char*)&c, 4);
		file.write((char *)&s, 4);
	}
	else
	{
		//ERROR
	}
}

