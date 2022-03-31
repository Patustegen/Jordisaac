#include "Hollow.h"
#include "Singletons.h"

Hollow::Hollow()
{
	gID = iResourceM->loadAndGetGraphicID("Assets\\Bosses\\hollowHead.png");
	gBody = iResourceM->loadAndGetGraphicID("Assets\\Bosses\\hollowBody.png");
	col = { 0,0,38,40,0,0 };
	paint = { 0,0,38,40,0,0 };
	hp = 32;
	orientacio = NO;
	angle = 0;
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
	angle = rand() % 360;
}

void Hollow::update()
{
	frame += iVideo->getDeltaTime() * 2;
	if (frame > 1999)
	{
		frame = 0;
	}
	float moveX = 0, moveY = 0;

	float vel = 1.5f * iVideo->getDeltaTime();
	//VelX = Vel * cos(angle)
	float velX = vel * cos(angle);

	//VelY = Vel * sin(angle)
	float velY = vel * sin(angle);


	col.restX = std::modf(col.restX, &moveX);
	col.restY = std::modf(col.restY, &moveY);
	col.x += moveX;
	col.y += moveY;

	paint.x = col.x;
	paint.y = col.y;
}

void Hollow::render()
{
	iVideo->renderGraphicEx(gID, &paint, angle, 2.0f, 2.0f, (frame / 1000) * paint.w, paint.h * orientacio);
}
