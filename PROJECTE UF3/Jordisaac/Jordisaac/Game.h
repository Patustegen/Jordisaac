#pragma once
#include "Scene.h"
#include "UI.h"
class Game :
    public Scene
{
private:
	Player* player;
	UI* ui;
	int bg;
public:
	Game();

	//! Handles the drawing of the scene
	void render();

	//! Handles the updating of the scene
	void update();

	//! Loads Scene Assets.
	void load();

	void init();
};

