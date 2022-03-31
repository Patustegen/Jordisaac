#include "Bullet.h"
#include "Singletons.h"

Bullet::Bullet(float vel, int t, float range, Rect* sp, LOOKING coord, DIAGONALS diagonals)
{
	initPos = { sp->x, sp->y };
	type = t;
	maxMove = range * 50;
	velocity = vel * 0.25f;
	col = { 0, 0, 22, 22, 0, 0 };
	paint = { 0, 0, 15, 15 };
	switch (coord)
	{
	case DOWN:
		dir = S;
		col.x = sp->x + sp->w - (col.w / 2);
		col.y = sp->y + col.h + sp->h;
		break;
	case RIGHT:
		col.x = sp->x + sp->w + col.w;
		col.y = sp->y + sp->h - (col.h / 2);
		dir = E;
		break;
	case UP:
		dir = N;
		col.x = sp->x + sp->w - (col.w / 2);
		col.y = sp->y - col.h;
		break;
	case LEFT:
		dir = W;
		col.x = sp->x - col.w;
		col.y = sp->y + sp->h - (col.h / 2);
		break;
	case NO:
		switch (diagonals)
		{
		case NE:
			col.x = sp->x + sp->w + col.w - 2;
			col.y = sp->y - col.h + 2;
			dir = N_E;
			break;
		case SE:
			col.x = sp->x + sp->w + col.w - 2;
			col.y = sp->y + col.h + sp->h - 2;
			dir = S_E;
			break;
		case SW:
			col.x = sp->x - col.w + 2;
			col.y = sp->y + col.h + sp->h - 2;
			dir = S_W;
			break;
		case NW:
			col.x = sp->x + sp->w + col.w - 2;
			col.y = sp->y + col.h + sp->h - 2;
			dir = N_W;
			break;
		default:
			break;
		}
		break;
	default:
		break;
	}
	destroy = false;
	load();
}

void Bullet::update()
{
	float moveX = 0, moveY = 0;
	switch (dir)
	{
	case N:
		col.restY -= velocity * iVideo->getDeltaTime();
		break;
	case N_E:
		col.restX += velocity * (iVideo->getDeltaTime() * 0.7f);
		col.restY -= velocity * (iVideo->getDeltaTime() * 0.7f);
		break;
	case E:
		col.restX += velocity * iVideo->getDeltaTime();
		break;
	case S_E:
		col.restX += velocity * (iVideo->getDeltaTime() * 0.7f);
		col.restY += velocity * (iVideo->getDeltaTime() * 0.7f);
		break;
	case S:
		col.restY += velocity * iVideo->getDeltaTime();
		break;
	case S_W:
		col.restX -= velocity * (iVideo->getDeltaTime() * 0.7f);
		col.restY += velocity * (iVideo->getDeltaTime() * 0.7f);
		break;
	case W:
		col.restX -= velocity * iVideo->getDeltaTime();
		break;
	case N_W:
		col.restX -= velocity * (iVideo->getDeltaTime() * 0.7f);
		col.restY -= velocity * (iVideo->getDeltaTime() * 0.7f);
		break;
	default:
		break;
	}
	col.restX = std::modf(col.restX, &moveX);
	col.restY = std::modf(col.restY, &moveY);
	col.x += moveX;
	col.y += moveY;

	paint.x = col.x;
	paint.y = col.y;


	if ((col.x - initPos.x >= maxMove || initPos.x - col.x >= maxMove) || (col.y - initPos.y >= maxMove || initPos.y - col.y >= maxMove))
	{
		destroy = true;
	}
}

void Bullet::render()
{
	iVideo->renderGraphic(gID, paint.x, paint.y, paint.w, paint.h, 0, 0, 1.5f, 1.5f);
}

void Bullet::load()
{
	gID = iResourceM->loadAndGetGraphicID("Assets\\Characters\\defaultTears.png");
}
