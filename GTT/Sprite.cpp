#include "Sprite.h"
#include "Game.h"
#include <iostream>


Sprite::Sprite(string path, int w, int h, int x, int y) {
	texture = new Texture(Game::renderer_, path);
	rect = new SDL_Rect();
	rect->h = h; rect->w = w; rect->x = x; rect->y = y;
}

Sprite::~Sprite() {
	texture->freeTexture();
	delete texture; texture = nullptr;
	delete rect; rect = nullptr;
}

void Sprite::render(Uint32 deltaTime) {
	texture->render(*rect);
}
