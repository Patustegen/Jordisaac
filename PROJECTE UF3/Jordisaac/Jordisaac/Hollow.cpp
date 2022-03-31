#include "Hollow.h"
#include "Singletons.h"

Hollow::Hollow()
{
	gID = iResourceM->loadAndGetGraphicID("Assets\\Bosses\\hollowHead.png");
	gBody = iResourceM->loadAndGetGraphicID("Assets\\Bosses\\hollowBody.png");
	col = { 0,0,38,40,0,0 };
	paint = { 0,0,38,40,0,0 };
	hp = 32;
}

Hollow::~Hollow()
{
}

void Hollow::init()
{
	col.x = SCREEN_WIDTH / 2 - col.w / 2;
	col.y = SCREEN_HEIGHT / 2 - col.h / 2;
	paint.x = col.x;
	paint.y = col.y;
}

void Hollow::update()
{


	paint.x = col.x;
	paint.y = col.y;
}

void Hollow::render()
{
	iVideo->renderGraphic(gID, paint.x, paint.y, paint.w, paint.h, frame * col.w, col.h, 2.0f, 2.0f);
}
