#pragma once
#include "Scene.h"

enum CHARACTERS {ISAAC, MAGDALENE, CAIN, SAMSON};

class ChooseCharacter :
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
	CHARACTERS aCharacter;
	int bgImage;
};

