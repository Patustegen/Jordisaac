#include "Ranking.h"
#include "Singletons.h"
#include "fstream"

using namespace std;

void Ranking::render()
{
	iVideo->renderGraphic(bgImage, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
	for (int i = 0; i < 10; i++)
	{
		if (i == 9)
		{
			iVideo->renderGraphic(gNums, 300, 65 + 40 * i, 8, 9, 8 *(( i +1) / 10), 0, 2.5f, 2.5f);
			iVideo->renderGraphic(gNums, 300 + 20, 65 + 40 * i, 8, 9, 8 *(( i +1) % 10), 0, 2.5f, 2.5f);
		}
		else iVideo->renderGraphic(gNums, 300, 65 + 40 * i, 8, 9, 8 *( i +1), 0, 2.5f, 2.5f);
		if (rPlayer[i] != -1)
		{
			iVideo->renderGraphic(gCharac, 370 + i %2 * 50, 65 + 40 * i - (90 * 0.3f) + (8 * 1.25f), 67, 90, 67 * rPlayer[i], 0, 0.6f,0.6f);
			int numbers = rScore[i];
			for (int j = 0; j < 4; j++)
			{
				iVideo->renderGraphic(gNums, 600 - 20 * j, 70 + 40 * i - (9 * 2) + (8 * 1.25f), 8, 9, 8 * (numbers % 10), 0, 2.0f, 2.0f);
				numbers /= 10;
			}
		}
	}
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
	bgImage = iResourceM->loadAndGetGraphicID("Assets/Menus/rankmenu.png");
	gNums = iResourceM->loadAndGetGraphicID("Assets/UI/UINumbers.png");
	gCharac = iResourceM->loadAndGetGraphicID("Assets/Characters/Choose.png");
}

void Ranking::init()
{
	for (int i = 0; i < 10; i++)
	{
		rPlayer[i] = -1;
		rScore[i] = 0;
	}

	streampos size;
	char* memblock;

	fstream file("rank.data", ios::in|ios::binary);
	if (file.is_open())
	{
		file.seekg(0, file.end);
		size = file.tellg();
		file.seekg(0, file.beg);
		memblock = new char[size];
		file.read(memblock, size);
		file.close();

		for (int i = 0; i < size / 4 / 2; i++)
		{
			rPlayer[i] = memblock[i * 4 * 2] | memblock[i * 4 * 2 + 1] | memblock[i * 4 * 2 + 2] | memblock[i * 4 * 2 + 3];
			rScore[i] = memblock[i * 4 * 2 + 4] | memblock[i * 4 * 2 + 1 + 4] | memblock[i * 4 * 2 + 2 + 4] | memblock[i * 4 * 2 + 3 + 4];
		}

		delete[] memblock;
	}
	else
	{
		cout << "Couldn't open file\n";
	}
}
