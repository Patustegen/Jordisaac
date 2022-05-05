#include "Pickup.h"
#include "Singletons.h"

void Pickup::update()
{
}

void Pickup::render()
{
	iVideo->renderGraphic(gID, paint.x, paint.y, paint.w, paint.h, paint.w * type, 0);
}

Pickup::Pickup(int x, int y, int t)
{
	type = t;
	room = iRoomM->getActualRoom()->getRoomID();
	gID = iResourceM->loadAndGetGraphicID("Assets/pickups/pickups.png");
	col = { x, y, 27, 23 };
	paint = { x, y, 27, 23 };
}

Pickup::~Pickup()
{
}
