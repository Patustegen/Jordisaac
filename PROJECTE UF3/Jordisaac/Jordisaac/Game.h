#pragma once
#include "Scene.h"
#include "Player.h"
class Game :
    public Scene
{
private:
	Player* player;
public:
	//! Handles the drawing of the scene
	void render();

	//! Handles the updating of the scene
	void update();

	//! Loads Scene Assets.
	void load();

	void init();
};

