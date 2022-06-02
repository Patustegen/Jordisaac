#include "Boss.h"
#include "Singletons.h"


Boss::Boss()
{
	bossMusic = iSoundM->loadAndGetSoundID("Assets/Music/win.mp3");
}

Boss::~Boss()
{
	iAudio->haltChannel();
	iAudio->playAudio(iSoundM->getSoundByID(bossMusic), 0);
}

void Boss::init()
{
}

void Boss::update()
{
}

void Boss::render()
{
}
