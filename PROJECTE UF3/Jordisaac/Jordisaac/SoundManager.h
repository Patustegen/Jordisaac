#pragma once
#include "SDL.h"
#include <iostream>
#include <map>
#include <vector>
#include "SDL_mixer.h"

class SoundManager
{
	static SoundManager* pInstance;
	std::vector<Mix_Chunk*>	mAudioVector;
	std::map<std::string, Sint32>	mIDMap;
	Uint32 mFirstFreeSlot;
	Uint32 updateFirstFreeSlotGraphic();
	Sint32 addAudio(const char* file);
protected:
	SoundManager();
public:
	~SoundManager();
	static SoundManager* getInstance()
	{
		if (pInstance == NULL) pInstance = new SoundManager();
		return pInstance;
	}
	Sint32 loadAndGetSoundID(const char* file);
	std::string getSoundPathByID(Sint32 ID);
	Mix_Chunk* getSoundByID(Sint32 ID);
	void removeSound(const char* file);
	void printLoadedAudio();
};

