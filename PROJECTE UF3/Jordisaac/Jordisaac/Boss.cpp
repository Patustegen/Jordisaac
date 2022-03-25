#include "Boss.h"
#include "Hollow.h"


Boss::Boss()
{
	int iboss = rand() % 3;

	iboss = 0;
	switch (iboss)
	{
	case 0:
		pInstance = new Hollow();
		break;
	case 1:
		break;
	case 2:
		break;
	default:
		break;
	}
}

Boss::~Boss()
{
}

void Boss::init()
{
}

void Boss::update()
{
}

void Boss::render()
{
}
