#include "Bullet.h"
#include "Singletons.h"

Bullet::Bullet(float vel, int t, float range, float dmg, Rect* sp, LOOKING coord, int a)
{
	initPos = { sp->x, sp->y };
	type = t;
	angle = a;
	damage = dmg;
	maxMove = (int)range * 50;
	velocity = vel * 0.25f;
	col = { 0, 0, 22, 22, 0, 0 };
	paint = { 0, 0, 15, 15 };

	switch (coord)
	{
	case DOWN:
		col.x = sp->x + sp->w - (col.w / 2);
		col.y = sp->y + col.h + sp->h;
		break;
	case RIGHT:
		col.x = sp->x + sp->w + col.w;
		col.y = sp->y + sp->h - (col.h / 2);
		break;
	case UP:
		col.x = sp->x + sp->w - (col.w / 2);
		col.y = sp->y - col.h;
		break;
	case LEFT:
		col.x = sp->x - col.w;
		col.y = sp->y + sp->h - (col.h / 2);
		break;
	default:
		break;
	}
	destroy = false;
	load();
	iAudio->playAudio(iSoundM->getSoundByID(sID[rand() % 3]));
}

Bullet::~Bullet()
{
	iAudio->playAudio(iSoundM->getSoundByID(sID[rand() % 3 + 3]));
}

void Bullet::update()
{
	float moveX = 0, moveY = 0;

	float vel = velocity * (float)iVideo->getDeltaTime();

	float velX = vel * cos(angle * PI / 180.0f);

	float velY = vel * sin(angle * PI / 180.0f);

	col.restX += velX;
	col.restY += velY;

	col.restX = std::modf(col.restX, &moveX);
	col.restY = std::modf(col.restY, &moveY);
	col.x += (int)moveX;
	col.y += (int)moveY;

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
	if (type == 0) gID = iResourceM->loadAndGetGraphicID("Assets/Enemies/defaultBlood.png");
	else gID = iResourceM->loadAndGetGraphicID("Assets\\Characters\\defaultTears.png");

	sID.push_back(iSoundM->loadAndGetSoundID("Assets/Characters/tearFire1.mp3"));
	sID.push_back(iSoundM->loadAndGetSoundID("Assets/Characters/tearFire1.mp3"));
	sID.push_back(iSoundM->loadAndGetSoundID("Assets/Characters/tearFire2.mp3"));
	sID.push_back(iSoundM->loadAndGetSoundID("Assets/Characters/tearImpact1.mp3"));
	sID.push_back(iSoundM->loadAndGetSoundID("Assets/Characters/tearImpact2.mp3"));
	sID.push_back(iSoundM->loadAndGetSoundID("Assets/Characters/tearImpact3.mp3"));
}
