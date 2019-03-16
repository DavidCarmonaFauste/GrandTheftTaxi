#pragma once

#include "Container.h"
#include "Texture.h"
#include "SDL.h"
#include "Vector2D.h"
#include "CameraType.h"

class Game;

class Camera :
	public Container
{
public:
	Camera(int width, int height, float zoom = 1);
	virtual ~Camera();

	void renderTexture(Texture* texture, SDL_Rect const& dest,
		SDL_Rect* clip = nullptr, double angle = 0);

	// Setters and getters
	void setPos(int x, int y, bool center = false);
	Vector2D getPos();
	void setSize(int w, int h, bool resetZoom = false);
	Vector2D getSize();
	void setZoom(float zoom, bool center = true);
	float getZoom();

private:
	SDL_Rect* cameraRect_;
	int w_, h_;

	float zoom_;
};

