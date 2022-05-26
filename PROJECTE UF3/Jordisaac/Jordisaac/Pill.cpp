#include "Pill.h"

void Pill::Use()
{
	switch (type)
	{
	case 0:
		break;
	case 1:
		break;
	case 2:
		break;
	case 3:
		break;
	case 4:
		break;
	case 5:
		break;
	default:
		break;
	}
}

Pill::Pill(int t, int s)
{
	type = t;
	sprite = s;
}

Pill::~Pill()
{
}
