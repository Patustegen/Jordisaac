#pragma once
#include "Scene.h"
class PauseMenu :
    public Scene
{
	//! Handles the drawing of the scene
	void render();

	//! Handles the updating of the scene
	void update();

	//! Loads Scene Assets.
	void load();
};

