#include "Bullet.h"
#include "Singletons.h"

Bullet::Bullet(float vel, int t, Rect* sp, LOOKING coord, DIAGONALS diagonals)
{
	time = 0;
	type = t;
	velocity = vel;
	col = { 0, 0, 22, 22 };
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
	load();
}

void Bullet::update()
{
	switch (dir)
	{
	case N:
		col.y -= velocity * iVideo->getDeltaTime();
		break;
	case N_E:
		col.x += velocity * (iVideo->getDeltaTime() * 0.7f);
		col.y -= velocity * (iVideo->getDeltaTime() * 0.7f);
		break;
	case E:
		col.x += velocity * iVideo->getDeltaTime();
		break;
	case S_E:
		col.x += velocity * (iVideo->getDeltaTime() * 0.7f);
		col.y += velocity * (iVideo->getDeltaTime() * 0.7f);
		break;
	case S:
		col.y += velocity * iVideo->getDeltaTime();
		break;
	case S_W:
		col.x -= velocity * (iVideo->getDeltaTime() * 0.7f);
		col.y += velocity * (iVideo->getDeltaTime() * 0.7f);
		break;
	case W:
		col.x -= velocity * iVideo->getDeltaTime();
		break;
	case N_W:
		col.x -= velocity * (iVideo->getDeltaTime() * 0.7f);
		col.y -= velocity * (iVideo->getDeltaTime() * 0.7f);
		break;
	default:
		break;
	}
	paint.x = col.x;
	paint.y = col.y;
}

void Bullet::render()
{
	iVideo->renderGraphic(gID, paint.x, paint.y, paint.w, paint.h, 0, 0, 1.5f, 1.5f);
}

void Bullet::load()
{
	gID = iResourceM->loadAndGetGraphicID("Assets\\Characters\\defaultTears.png");
}
