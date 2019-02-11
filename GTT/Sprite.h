#pragma once

#include "Texture.h"
#include "RenderComponent.h"
#include <vector>
#include <map>

using namespace std;


class Sprite : public RenderComponent {

public:
	Sprite(string path = "./../Assets/sprites/default.png",
		   int w = 100, int h = 100,
		   int x = 0, int y = 0);
	virtual ~Sprite();

	virtual void render(GameObject* o, Uint32 deltaTime) override;

private:
	Texture *texture;
	SDL_Rect *rect;
};
