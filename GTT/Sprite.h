#pragma once

#include "Texture.h"
#include "RenderComponent.h"
#include "Camera.h"
#include <vector>
#include <map>

using namespace std;


class Sprite : public RenderComponent {

public:
	Sprite(string path = "./../Assets/sprites/default.png",
		   int w = 100, int h = 100,
		   int x = 0, int y = 0);

	Sprite(Texture* texture,
		   int w = 100, int h = 100,
		   int x = 0, int y = 0);

	virtual ~Sprite();

	virtual void render(GameObject* o, Uint32 deltaTime) override;

	void setCamera(cameraType cam);
	void setClipRect(SDL_Rect *clip);

private:
	Texture *texture_;
	SDL_Rect *rect_;
	SDL_Rect *clip_ = nullptr;

	cameraType cam_ = GAME_CAMERA;
};
