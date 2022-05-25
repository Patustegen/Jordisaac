#include "Hollow.h"

void Hollow::init()
{
	int a = rand() % 360;
	for (int i = 0; i < mHBody.size(); i++)
	{
		mHBody[i]->init();
		mHBody[i]->setAngle(a);
	}
}

void Hollow::update()
{
	for (int i = 0; i < mHBody.size(); i++)
	{
		mHBody[i]->update();
	}
}

void Hollow::render()
{
	for (int i = 0; i < mHBody.size(); i++)
	{
		mHBody[i]->render();
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
}
