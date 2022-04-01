#include "Hollow.h"
#include "Singletons.h"
#define PI 3.14159265

Hollow::Hollow()
{
	gID = iResourceM->loadAndGetGraphicID("Assets\\Bosses\\hollowHead.png");
	gBody = iResourceM->loadAndGetGraphicID("Assets\\Bosses\\hollowBody.png");
	col = { 0,0,76,80,0,0 };
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
	float velX = vel * cos(angle * PI / 180.0);

	//VelY = Vel * sin(angle)
	float velY = vel * sin(angle * PI / 180.0);

	col.restX += velX;
	col.restY += velY;

	col.restX = std::modf(col.restX, &moveX);
	col.restY = std::modf(col.restY, &moveY);
	col.x += moveX;
	col.y += moveY;


	if (col.x < ROOM_MARGIN_X)
	{
		col.x = ROOM_MARGIN_X;

		if (angle > 90 && angle <= 180) angle = (90 - (angle - 90)) + rand() % 10 -4;
		else if (angle > 180 && angle < 270) angle = (270 + (270 - angle)) + rand() % 10 -4;
		//angle = rand() % 360;
	}
	else if (col.x > SCREEN_WIDTH - ROOM_MARGIN_X - col.w) 
	{
		col.x = SCREEN_WIDTH - ROOM_MARGIN_X - col.w;
		
		if (angle >= 0 && angle < 90) angle = (180 - angle) + rand() % 10 -4;
		else if (angle > 270 && angle < 360) angle = (180 + (360 - angle)) + rand() % 10 -4;
		//angle = rand() % 360;
	}
	if (col.y < ROOM_MARGIN_Y)
	{
		col.y = ROOM_MARGIN_Y;
		
		if (angle > 180 && angle <= 270) angle = (180 - (angle - 180)) + rand() % 10 -4;
		else if (angle > 270 && angle < 360) angle = (90 - (angle - 270)) + rand() % 10 -4;
		//angle = rand() % 360;
	}
	else if (col.y > SCREEN_HEIGHT - ROOM_MARGIN_Y - col.h)
	{
		col.y = SCREEN_HEIGHT - ROOM_MARGIN_Y - col.h;
		
		if (angle > 0 && angle <= 90) angle = (360 - angle) + rand() % 10 -4;
		else if (angle > 90 && angle < 180) angle = (180 + (180 - angle)) + rand() % 10 -4;
		//angle = rand() % 360;
	}

	if (angle < 112 && angle > 68) orientacio = DOWN;
	else if (angle <= 68 || angle >= 338) orientacio = RIGHT;
	else if (angle < 338 && angle > 248) orientacio = UP;
	else if (angle <= 248 && angle >= 112) orientacio = LEFT;
	std::cout << angle << std::endl;
	paint.x = col.x;
	paint.y = col.y;
}

void Hollow::render()
{
	iVideo->renderGraphicEx(gID, &paint, 0, 2.0f, 2.0f, (frame / 1000) * paint.w, paint.h * orientacio);
}
