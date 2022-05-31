#include "HollowBody.h"
#include "Singletons.h"

HollowBody::HollowBody(bool h)
{
	head = h;
	rebotes = { 0,0,76,80,0,0 };
	if (head)
	{
		gID = iResourceM->loadAndGetGraphicID("Assets\\Bosses\\hollowHead.png");
		col = { 0,0,76,80,0,0 };
		paint = { 0,0,38,40,0,0 };
	}
	else
	{
		gID = iResourceM->loadAndGetGraphicID("Assets\\Bosses\\hollowBody.png");
		col = { 0,0,54,46,0,0 };
		paint = { 0,0,27,23,0,0 };
	}
	orientacio = NO;
	angle = 0;
	touched = false;
}

HollowBody::~HollowBody()
{
}

void HollowBody::init()
{
	rebotes.x = SCREEN_WIDTH / 2 - rebotes.w / 2;
	rebotes.y = SCREEN_HEIGHT / 2 - rebotes.h / 2;
	if (head)
	{
		col.x = rebotes.x;
		col.y = rebotes.y;
	}
	else
	{
		col.x = rebotes.x + 11;
		col.y = rebotes.y + 17;
	}
	paint.x = col.x;
	paint.y = col.y;
	touched = false;
}

void HollowBody::update()
{
	touched = false;
	frame += iVideo->getDeltaTime() * 2;
	if (frame > 1999)
	{
		frame = 0;
	}
	float moveX = 0, moveY = 0;

	float vel = 0.35f * iVideo->getDeltaTime();

	float velX = vel * cos(angle * PI / 180.0f);

	float velY = vel * sin(angle * PI / 180.0f);

	rebotes.restX += velX;
	rebotes.restY += velY;

	rebotes.restX = std::modf(rebotes.restX, &moveX);
	rebotes.restY = std::modf(rebotes.restY, &moveY);
	rebotes.x += (int)moveX;
	rebotes.y += (int)moveY;


	if (rebotes.x < ROOM_MARGIN_X)
	{
		rebotes.x = ROOM_MARGIN_X;

		if (angle > 90 && angle <= 180) angle = (90 - (angle - 90)) /*+ rand() % 10 -4*/;
		else if (angle > 180 && angle < 270) angle = (270 + (270 - angle)) /*+ rand() % 10 -4*/;
	}
	else if (rebotes.x > SCREEN_WIDTH - ROOM_MARGIN_X - rebotes.w) 
	{
		rebotes.x = SCREEN_WIDTH - ROOM_MARGIN_X - rebotes.w;
		
		if (angle >= 0 && angle < 90) angle = (180 - angle) /*+ rand() % 10 -4*/;
		else if (angle > 270 && angle < 360) angle = (180 + (360 - angle)) /*+ rand() % 10 -4*/;
	}
	if (rebotes.y < ROOM_MARGIN_Y)
	{
		rebotes.y = ROOM_MARGIN_Y;
		
		if (angle > 180 && angle <= 270) angle = (180 - (angle - 180)) /*+ rand() % 10 -4*/;
		else if (angle > 270 && angle < 360) angle = (90 - (angle - 270)) /*+ rand() % 10 -4*/;
	}
	else if (rebotes.y > SCREEN_HEIGHT - ROOM_MARGIN_Y - rebotes.h)
	{
		rebotes.y = SCREEN_HEIGHT - ROOM_MARGIN_Y - rebotes.h;
		
		if (angle > 0 && angle <= 90) angle = (360 - angle) /*+ rand() % 10 -4*/;
		else if (angle > 90 && angle < 180) angle = (180 + (180 - angle)) /*+ rand() % 10 -4*/;
	}

	if (angle < 112 && angle > 68) orientacio = DOWN;
	else if (angle <= 68 || angle >= 338) orientacio = RIGHT;
	else if (angle < 338 && angle > 248) orientacio = UP;
	else if (angle <= 248 && angle >= 112) orientacio = LEFT;

	if (head)
	{
		col.x = rebotes.x;
		col.y = rebotes.y;
	}
	else
	{
		col.x = rebotes.x + 11;
		col.y = rebotes.y + 17;
	}

	paint.x = col.x;
	paint.y = col.y;
}

void HollowBody::render()
{
	iVideo->renderGraphicEx(gID, &paint, 0, 2.0f, 2.0f, (frame / 1000) * paint.w, paint.h * orientacio);
}

void HollowBody::hurt(float h)
{
	touched = true;
}
