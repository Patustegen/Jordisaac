#pragma once
#include "sdl.h"
#include "Utils.h"
class Video
{
	static Video* pInstance;
	SDL_Window* gWindow;
	SDL_Renderer* gRenderer;
	unsigned int lastTime, currentTime, deltaTime;
	float msFrame;
protected:
	Video();
public:
	static Video* getInstance() 
	{
		if (pInstance == NULL) pInstance = new Video();
		return pInstance;
	}
	~Video();
	void renderGraphic(int img, int posX, int posY, int width, int height, int gx = 0, int gy = 0, float wScale = 1, float hScale = 1);
	void clearScreen(unsigned int color_key);
	void updateScreen();
	void waitTime(int ms);
	int getTicks() { return SDL_GetTicks(); };
	int getDeltaTime() { return deltaTime; };
	void updateTime();
	SDL_Renderer* getRenderer() { return gRenderer; };
	void close();
};