#include "SoundManager.h"

SoundManager* SoundManager::pInstance = NULL;

Uint32 SoundManager::updateFirstFreeSlotGraphic()
{
	for (int i = 0; i < mAudioVector.size(); i++)
	{
		if (mAudioVector.at(i) == NULL)
		{
			mFirstFreeSlot = i;
			return i;
		}
	}
	mFirstFreeSlot = mAudioVector.size();
	return mFirstFreeSlot;
}

Sint32 SoundManager::addAudio(const char* file)
{
	Mix_Chunk* n = Mix_LoadWAV(file);
	if (n == NULL)
	{
		return -1;
	}
	if (mFirstFreeSlot == mAudioVector.size())
	{
		mAudioVector.push_back(n);
	}
	else
	{
		mAudioVector.at(mFirstFreeSlot) = n;
	}
	mIDMap.emplace(file, mFirstFreeSlot);
	updateFirstFreeSlotGraphic();
}

SoundManager::SoundManager()
{
	mFirstFreeSlot = 0;
	mAudioVector.resize(0);
	mIDMap.empty();
}

SoundManager::~SoundManager()
{
}

Sint32 SoundManager::loadAndGetSoundID(const char* file)
{
	std::map<std::string, Sint32>::iterator it = mIDMap.find(file);
	if (it == mIDMap.end())
	{
		if (addAudio(file) == -1)
		{
			std::cout << SDL_GetError();
			return -1;
		}
	}
	it = mIDMap.find(file);
	return it->second;
}

std::string SoundManager::getSoundPathByID(Sint32 ID)
{
	for (std::map<std::string, Sint32>::iterator it = mIDMap.begin(); it != mIDMap.end(); ++it)
	{
		if (it->second == ID)
		{
			return it->first;
		}
	}
}

Mix_Chunk* SoundManager::getSoundByID(Sint32 ID)
{
	return mAudioVector.at(ID);
}

void SoundManager::removeSound(const char* file)
{
	std::map<std::string, Sint32>::iterator it = mIDMap.find(file);
	if (it != mIDMap.end())
	{
		//Not Found
	}
	else
	{
		Mix_FreeChunk(mAudioVector.at(it->second));
	}
	updateFirstFreeSlotGraphic();
}

void SoundManager::printLoadedAudio()
{
	for (std::map<std::string, Sint32>::iterator it = mIDMap.begin(); it != mIDMap.end(); ++it)
	{
		printf("%s\n", it->first);
	}
}
