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

	float vel = 0.35f * iVideo->getDeltaTime();
	//VelX = Vel * cos(angle)
	float velX = vel * cos(angle);

	//VelY = Vel * sin(angle)
	float velY = vel * sin(angle);

	col.restX += velX;
	col.restY += velY;

	col.restX = std::modf(col.restX, &moveX);
	col.restY = std::modf(col.restY, &moveY);
	col.x += moveX;
	col.y += moveY;


	if (col.x < ROOM_MARGIN_X)
	{
		col.x = ROOM_MARGIN_X;
		angle = 180 - angle;
		//angle = rand() % 360;
	}
	else if (col.x > SCREEN_WIDTH - ROOM_MARGIN_X - col.w) 
	{
		col.x = SCREEN_WIDTH - ROOM_MARGIN_X - col.w;
		angle = 180 - angle;
		//angle = rand() % 360;
	}
	if (col.y < ROOM_MARGIN_Y)
	{
		col.y = ROOM_MARGIN_Y;
		angle = 360 - angle;
		//angle = rand() % 360;
	}
	else if (col.y > SCREEN_HEIGHT - ROOM_MARGIN_Y - col.h)
	{
		col.y = SCREEN_HEIGHT - ROOM_MARGIN_Y - col.h;
		angle = 360 - angle;
		//angle = rand() % 360;
	}


	//> <

	if (angle > 315 || angle < 45) orientacio = RIGHT;
	else if (angle <= 135 && angle >= 45) orientacio = DOWN;
	else if (angle < 225 && angle > 135) orientacio = LEFT;
	else if (angle <= 315 && angle >= 225) orientacio = UP;
	std::cout << angle << std::endl;
	paint.x = col.x;
	paint.y = col.y;
}

void Hollow::render()
{
	iVideo->renderGraphicEx(gID, &paint, 0, 2.0f, 2.0f, (frame / 1000) * paint.w, paint.h * orientacio);
}
