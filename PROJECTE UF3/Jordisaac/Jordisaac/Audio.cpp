#include "Audio.h"

Audio* Audio::pInstance = NULL;

Audio::Audio()
{
	SDL_Init(SDL_INIT_AUDIO);
	Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 1024);
	Mix_AllocateChannels(128);
}

Audio::~Audio()
{
}

void Audio::setPosition(Sint32 channel, Sint16 angle, Sint8 distance)
{
	Mix_SetPosition(channel, angle, distance);
}

void Audio::haltChannel(int channel)
{
	Mix_HaltChannel(channel);
}

void Audio::pauseChannel(int channel)
{
	Mix_Pause(channel);
}

void Audio::resumeChannel(int channel)
{
	Mix_Resume(channel);
}

int Audio::playAudio(Mix_Chunk* audio, int channel, int repeat)
{
	return Mix_PlayChannel(channel, audio, repeat);
}
