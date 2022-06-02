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
		iAudio->haltChannel();
		iSceneD->changeScene(MAIN);
		iSceneD->getCurrentScene()->init();
	}
}

void GameOver::load()
{
}

void GameOver::init(int s)
{
	int rPlayer[10];
	int rScore[10];

	for (int i = 0; i < 10; i++)
	{
		rPlayer[i] = -1;
		rScore[i] = 0;
	}

	streampos size;
	char* memblock;

	fstream fileRead("rank.data", ios::in | ios::binary);
	if (fileRead.is_open())
	{
		fileRead.seekg(0, fileRead.end);
		size = fileRead.tellg();
		fileRead.seekg(0, fileRead.beg);
		memblock = new char[size];
		fileRead.read(memblock, size);
		fileRead.close();

		for (int i = 0; i < size / 4 / 2; i++)
		{
			if (i < 10)
			{
				rPlayer[i] = memblock[i * 4 * 2] | memblock[i * 4 * 2 + 1] | memblock[i * 4 * 2 + 2] | memblock[i * 4 * 2 + 3];
				rScore[i] = memblock[i * 4 * 2 + 4] | memblock[i * 4 * 2 + 1 + 4] | memblock[i * 4 * 2 + 2 + 4] | memblock[i * 4 * 2 + 3 + 4];
			}
		}
		delete[] memblock;


		int temp[2] = { -1, 0 };
		bool placed = false;
		for (int i = 0; i < 10; i++)
		{
			if (rPlayer[i] != -1)
			{
				if (temp[0] == -1)
				{
					if (!placed)
					{
						if (rScore[i] < s)
						{
							temp[0] = rPlayer[i];
							temp[1] = rScore[i];
							rScore[i] = s;
							rPlayer[i] = iSceneD->getSelectedCharacter();
							placed = true;
						}
					}
				}
				else
				{
					if (rScore[i] < temp[1])
					{
						int temptemp[2];
						temptemp[0] = rPlayer[i];
						temptemp[1] = rScore[i];
						rPlayer[i] = temp[0];
						rScore[i] = temp[1];
						temp[0] = temptemp[0];
						temp[1] = temptemp[1];
					}
					else
					{
						temp[0] = -1;
						temp[1] = 0;
					}
				}
			}
			else
			{
				if (temp[0] == -1)
				{
					if (!placed)
					{
						rScore[i] = s;
						rPlayer[i] = iSceneD->getSelectedCharacter();
						placed = true;
					}
				}
				else
				{
					rPlayer[i] = temp[0];
					rScore[i] = temp[1];
					temp[0] = -1;
					temp[1] = 0;
				}
			}
		}

	}
	else
	{
		cout << "Couldn't open file\n";
	}

	fstream fileWrite("rank.data", ios::out | ios::binary);
	if (fileWrite.is_open())
	{
		for (int i = 0; i < 10; i++)
		{
			if (rPlayer[i] != -1)
			{
				fileWrite.write((char*)&rPlayer[i], 4);
				fileWrite.write((char*)&rScore[i], 4);
			}
		}
		fileWrite.close();
	}
	else
	{
		cout << "Couldn't open file\n";
	}
}

