#pragma once
#include "Scene.h"
class GameOver :
    public Scene
{
public:
	//! Handles the drawing of the scene
	void render();

	//! Handles the updating of the scene
	void update();

	//! Loads Scene Assets.
	void load();

	void init(int s = 0);
};

