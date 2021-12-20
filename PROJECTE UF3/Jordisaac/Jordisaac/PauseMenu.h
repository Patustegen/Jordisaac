#pragma once
#include "Scene.h"

enum sPause
{
	P_OPTIONS, RESUME, EXIT
};

class PauseMenu :
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
	sPause selected;
};

