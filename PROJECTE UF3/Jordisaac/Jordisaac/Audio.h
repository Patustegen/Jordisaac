#pragma once
#include "SDL.h"
#include "SDL_mixer.h"
#include <iostream>

class Audio
{
	static Audio* pInstance;
protected:
	Audio();
public:
	~Audio();
	static Audio* getInstance()
	{
		if (pInstance == NULL) pInstance = new Audio();
		return pInstance;
	}
	void setPosition(Sint32 channel, Sint16 angle, Sint8 distance);
	void haltChannel(int channel = -1);
	void pauseChannel(int channel = -1);
	void resumeChannel(int channel = -1);
	int playAudio(Mix_Chunk* audio, int channel = -1, int repeat = 0);
};

