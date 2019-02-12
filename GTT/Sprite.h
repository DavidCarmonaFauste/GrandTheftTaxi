#pragma once

#include "Texture.h"
#include <vector>
#include <map>

using namespace std;


class Sprite {

public:
	Sprite(string path = "./../Assets/sprites/default.png",
		   int w = 100, int h = 100,
		   int x = 0, int y = 0);
	virtual ~Sprite();

	void render(Uint32 deltaTime);

private:
	Texture *texture;
	SDL_Rect *rect;
};
