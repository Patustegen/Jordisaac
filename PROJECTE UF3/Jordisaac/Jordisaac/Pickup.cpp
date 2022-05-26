#include "Pickup.h"
#include "Singletons.h"


void Pickup::render()
{
	iVideo->renderGraphic(gID, paint.x, paint.y, paint.w, paint.h, paint.w * id, 0, 1.5f, 1.5f);
}

Pickup::Pickup(int x, int y, int i, PICKUP_TYPE t)
{
	type = t;
	id = i;
	room = iRoomM->getActualRoom()->getRoomID();
	switch (t)
	{
	case NORMAL_PU:
		gID = iResourceM->loadAndGetGraphicID("Assets/pickups/pickups.png");
		col = { x + 5, y + 5, 27, 23 };
		paint = { x, y, 27, 23 };
		break;
	case CONS_PU:
		gID = iResourceM->loadAndGetGraphicID("Assets/Pills/Pills.png");
		col = { x + 2, y + 2, 17, 19 };
		paint = { x, y, 17, 19 };
		break;
	case PASSIVE_PU:
		break;
	case ACTIVE_PU:
		break;
	case TRINKET_PU:
		break;
	default:
		break;
	}
}

Pickup::~Pickup()
{
}
