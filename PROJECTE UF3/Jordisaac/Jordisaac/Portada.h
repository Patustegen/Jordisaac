#pragma once
#include "Scene.h"

class Portada :
    public Scene
{
public:
	//! Handles the drawing of the scene
	void render();

	//! Handles the updating of the scene
	void update();

	//! Loads Scene Assets.
	void load();

	void init();

private:
	int iScaled;
	int dScaled;
};

