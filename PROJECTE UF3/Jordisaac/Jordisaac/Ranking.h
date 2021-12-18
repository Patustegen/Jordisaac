#pragma once
#include "Scene.h"
class Ranking :
    public Scene
{
	//! Handles the drawing of the scene
	void render();

	//! Handles the updating of the scene
	void update();

	//! Loads Scene Assets.
	void load();
};

