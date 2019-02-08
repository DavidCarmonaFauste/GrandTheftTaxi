#include "Sprite.h"
#include "Game.h"
#include <iostream>

Sprite::Sprite(string path, int w, int h, int x, int y) {
	texture = new Texture(Game::renderer, path);
	rect = new SDL_Rect();
	rect->h = h; rect->w = w; rect->x = x; rect->y = y;
}

Sprite::~Sprite() {
	texture->freeTexture();
	delete texture;
	delete rect;
}

void Sprite::update(double deltaTime) {
	texture->render(*rect);
}

