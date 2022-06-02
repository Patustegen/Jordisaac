#include "Video.h"
#include "ResourceManager.h"

Video* Video::pInstance = NULL;

Video::Video() {
	msFrame = 1 / (FPS / 1000.0f);
	lastTime = 0;
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
void Video::clearScreen() {
	SDL_RenderClear(gRenderer);
}
void Video::updateScreen() {
	SDL_RenderPresent(gRenderer);
}
void Video::renderGraphicEx(int img, Rect* srcRect, double angle, float wScale, float hScale, int gx, int gy)
{
	SDL_Rect r, rectAux;
	r.x = gx;
	r.y = gy;
	r.w = srcRect->w;
	r.h = srcRect->h;
	rectAux.h = srcRect->h * hScale;
	rectAux.w = srcRect->w * hScale;
	rectAux.x = srcRect->x;
	rectAux.y = srcRect->y;
	SDL_Texture* origin = ResourceManager::getInstance()->getGraphicByID(img);
	SDL_RenderCopyEx(gRenderer, origin, &r, &rectAux, angle, NULL, SDL_FLIP_NONE);
}
void Video::waitTime(int ms) {
	SDL_Delay(ms);
}
bool Video::isInside(Rect* outside, Rect* inside)
{
	if ((inside->x > outside->x && inside->y > outside->y) && ((inside->x + inside->w) < (outside->x + outside->w) && (inside->y + inside->h) < (outside->y + outside->h)))
	{
		return true;
	}
	return false;
}
void Video::updateTime()
{
	currentTime = getTicks();
	deltaTime = currentTime - lastTime;
	if (deltaTime < (int)msFrame) {
		waitTime((int)msFrame - deltaTime);
	}
	lastTime = currentTime;
}
void Video::saveScreenshot()
{
	SDL_Surface* surface = SDL_CreateRGBSurfaceWithFormat(0, SCREEN_WIDTH, SCREEN_HEIGHT, 32, SDL_PIXELFORMAT_ARGB8888);
	SDL_RenderReadPixels(gRenderer, NULL, SDL_PIXELFORMAT_ARGB8888, surface->pixels, surface->pitch);
	SDL_SaveBMP(surface, "Assets/Menus/screenshot.bmp");
	SDL_FreeSurface(surface);
}
void Video::close() {
}
bool Video::onCollision(Rect* a, Rect* b) 
{
	SDL_Rect A{ a->x,a->y,a->w,a->h };
	SDL_Rect B{ b->x,b->y,b->w,b->h };
	return SDL_HasIntersection(&A, &B);
}

