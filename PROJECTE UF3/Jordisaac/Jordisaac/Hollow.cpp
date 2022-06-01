#include "Hollow.h"

void Hollow::init()
{
	int a = rand() % 360;
	for (int i = 0; i < mHBody.size(); i++)
	{
		mHBody[i]->init();
		mHBody[i]->setAngle(a);
	}
	movBody = mHBody;
}

void Hollow::update()
{
	for (int i = 0; i < mHBody.size(); i++)
	{
		if (!mHBody[i]->isInited())
		{
			int distance_x = (mHBody[i]->getCol()->x + mHBody[i]->getCol()->w / 2) - (mHBody[i - 1]->getCol()->x + mHBody[i - 1]->getCol()->w / 2);
			int distance_y = (mHBody[i]->getCol()->y + mHBody[i]->getCol()->h / 2) - (mHBody[i - 1]->getCol()->y + mHBody[i - 1]->getCol()->h / 2);

			if (distance_x >= 25 || distance_x <= -25 || distance_y >= 15 || distance_y <= -15) mHBody[i]->update();
		}
		else
		{
			mHBody[i]->update();
			if (mHBody[i]->hasTouched()) hp--;
		}
	}
	movBody = mHBody;
	bool swapped;
	do
	{
		swapped = true;
		for (int i = 1; i < movBody.size(); i++)
		{
			if (movBody[i - 1]->getCol()->y + movBody[i - 1]->getCol()->h > movBody[i]->getCol()->y + movBody[i]->getCol()->h)
			{
				HollowBody* tmp = movBody[i - 1];
				movBody[i - 1] = movBody[i];
				movBody[i] = tmp;
				swapped = false;
			}
		}
	} while (!swapped);
}

void Hollow::render()
{
	for (int i = 0; i < movBody.size(); i++)
	{
		movBody[i]->render();
	}
}

Hollow::Hollow()
{
	mHBody.resize(5);
	hp = 32;
	mHBody[0] = new HollowBody(true);
	for (int i = 1; i < mHBody.size(); i++)
	{
		mHBody[i] = new HollowBody();
	}
}

Hollow::~Hollow()
{
	for (int i = 0; i < mHBody.size(); i++)
	{
		delete mHBody[i];
		mHBody.erase(mHBody.begin() + i);
		i--;
	}
}
