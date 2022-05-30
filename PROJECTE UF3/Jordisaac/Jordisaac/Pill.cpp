#include "Pill.h"
#include "Singletons.h"

void Pill::setPill(int t, int s)
{
	type = t;
	sprite = s;
}

void Pill::render()
{
	if (type != -1) iVideo->renderGraphic(gID, paint.x, paint.y, paint.w, paint.h, sprite * paint.w, 0, 3.0f, 3.0f);
}

void Pill::Use()
{
	type = -1;
	sprite = -1;
}

Pill::Pill()
{
	type = -1;
	sprite = -1;
	paint = { SCREEN_WIDTH - 70, SCREEN_HEIGHT - 70, 17, 19 };
	gID = iResourceM->loadAndGetGraphicID("Assets/Pills/Pills.png");
}

Pill::~Pill()
{
}
