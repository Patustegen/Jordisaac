#include "ResourceManager.h"
#include "ResourceManager.h"
#include <SDL_image.h>
#include "Video.h"

ResourceManager* ResourceManager::pInstance = NULL;

ResourceManager::~ResourceManager()
{
}

void ResourceManager::removeGraphic(const char* file)
{
	std::map<std::string, Sint32>::iterator it = mIDMap.find(file);
	if (it != mIDMap.end())
	{
		//Not Found
	}
	else
	{
		SDL_DestroyTexture(mGraphicsVector.at(it->second));
	}
	updateFirstFreeSlotGraphic();
}

Sint32 ResourceManager::loadAndGetGraphicID(const char* file)
{
	std::map<std::string, Sint32>::iterator it = mIDMap.find(file);
	if (it == mIDMap.end())
	{
		if (addGraphic(file) == -1)
		{
			return -1;
		}
	}
	it = mIDMap.find(file);
	return it->second;
}

std::string ResourceManager::getGraphicPathByID(Sint32 ID)
{
	for (std::map<std::string, Sint32>::iterator it = mIDMap.begin(); it != mIDMap.end(); ++it) 
	{
		if (it->second == ID)
		{
			return it->first;
		}
	}
}

void ResourceManager::getGraphicSize(Sint32 img, int& width, int& height)
{
	width = getGraphicWidth(img);
	height = getGraphicHeight(img);
}

Uint16 ResourceManager::getGraphicWidth(Sint32 img)
{
	int w;
	SDL_QueryTexture(mGraphicsVector.at(img), NULL, NULL, &w, NULL);
	return w;
}

Uint16 ResourceManager::getGraphicHeight(Sint32 img)
{
	int h;
	SDL_QueryTexture(mGraphicsVector.at(img), NULL, NULL, NULL, &h);
	return h;
}

SDL_Texture* ResourceManager::getGraphicByID(Sint32 ID)
{
	return mGraphicsVector.at(ID);
}

void ResourceManager::setAlphaGraphic(Sint32 ID, Uint8 alpha_value)
{
	SDL_SetTextureAlphaMod(getGraphicByID(ID), alpha_value);
}

void ResourceManager::printLoadedGraphics()
{
	for (std::map<std::string, Sint32>::iterator it = mIDMap.begin(); it != mIDMap.end(); ++it)
	{
		printf("%s\n", it->first);
	}
}

Sint32 ResourceManager::createGraphic(const char* name, Uint16 width, Uint16 height)
{
	SDL_Surface* s = SDL_CreateRGBSurface(0, width, height, 32, 0, 0, 0, 0);
	SDL_Texture* n = SDL_CreateTextureFromSurface(Video::getInstance()->getRenderer(),s);
	if (n == NULL)
	{
		return -1;
	}
	if (mFirstFreeSlot == mGraphicsVector.size())
	{
		mGraphicsVector.push_back(n);
	}
	else
	{
		mGraphicsVector.at(mFirstFreeSlot) = n;
	}
	mIDMap.emplace(name, mFirstFreeSlot);
	updateFirstFreeSlotGraphic();
}

ResourceManager::ResourceManager()
{
	mGraphicsVector.resize(0);
	mIDMap.empty();
	mFirstFreeSlot = 0;
	IMG_Init(IMG_INIT_PNG);
}

Sint32 ResourceManager::addGraphic(const char* file)
{
	SDL_Texture* n = IMG_LoadTexture(Video::getInstance()->getRenderer(),file);
	if (n == NULL)
	{
		return -1;
	}
	if (mFirstFreeSlot == mGraphicsVector.size())
	{
		SDL_SetTextureBlendMode(n, SDL_BLENDMODE_BLEND);
		mGraphicsVector.push_back(n);
	}
	else
	{
		mGraphicsVector.at(mFirstFreeSlot) = n;
	}
	mIDMap.emplace(file, mFirstFreeSlot);
	updateFirstFreeSlotGraphic();
}

Uint32 ResourceManager::updateFirstFreeSlotGraphic()
{
	for (int i = 0; i < mGraphicsVector.size(); i++)
	{
		if (mGraphicsVector.at(i) == NULL)
		{
			mFirstFreeSlot = i;
			return i;
		}
	}
	mFirstFreeSlot = mGraphicsVector.size();
	return mFirstFreeSlot;
}
