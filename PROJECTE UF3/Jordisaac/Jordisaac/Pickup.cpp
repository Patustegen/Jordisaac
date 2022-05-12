#include "Pickup.h"
#include "Singletons.h"


void Pickup::render()
{
	iVideo->renderGraphic(gID, paint.x, paint.y, paint.w, paint.h, paint.w * type, 0, 1.5f, 1.5f);
	iVideo->renderGraphic(frame, col.x, col.y, col.w, col.h);
}

Pickup::Pickup(int x, int y, int t)
{
	type = t;
	room = iRoomM->getActualRoom()->getRoomID();
	gID = iResourceM->loadAndGetGraphicID("Assets/pickups/pickups.png");
	frame = iResourceM->loadAndGetGraphicID("Assets/Characters/frame.png");
	col = { x + 5, y + 5, 27, 23 };
	paint = { x, y, 27, 23 };
}

Pickup::~Pickup()
{
}
