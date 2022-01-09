#pragma once
#include "Scene.h"
#include "enums.h"

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

	ChooseCharacter();
private:
	CHARACTERS aCharacter;
	CHARACTERS bCharacter;
	CHARACTERS nCharacter;
	int bgImage;
	int characs;
};

