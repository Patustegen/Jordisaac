#include "Video.h"
#include "ResourceManager.h"

Video* Video::pInstance = NULL;

Video::Video() {
	gWindow = NULL;
	gRenderer = NULL;
	SDL_Init(SDL_INIT_VIDEO);
	gWindow = SDL_CreateWindow("Jordisaac", SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
	gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC | SDL_RENDERER_TARGETTEXTURE);
}
Video::~Video() {
}
void Video::renderGraphic(int img, int posX, int posY, int width, int height, int gx, int gy, float wScale, float hScale) {
	SDL_Rect r, rectAux;
	r.x = gx;
	r.y = gy;
	r.w = width;
	r.h = height;
	rectAux.h = height * hScale;
	rectAux.w = width * wScale;
	rectAux.x = posX;
	rectAux.y = posY;
	SDL_Texture* origin = ResourceManager::getInstance()->getGraphicByID(img);
	SDL_RenderCopy(gRenderer, origin, &r, &rectAux);
}
void Video::clearScreen(unsigned int color_key) {
	SDL_RenderClear(gRenderer);
}
void Video::updateScreen() {
	SDL_RenderPresent(gRenderer);
}
void Video::waitTime(int ms) {
	SDL_Delay(ms);
}
void Video::close() {
}

