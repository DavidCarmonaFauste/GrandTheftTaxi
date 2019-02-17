#include "Sprite.h"
#include "Game.h"
#include <iostream>


Sprite::Sprite(string path, int w, int h, int x, int y) {
	texture_ = new Texture(Game::renderer_, path);
	rect_ = new SDL_Rect();
	rect_->h = h; rect_->w = w; rect_->x = x; rect_->y = y;
}

Sprite::~Sprite() {
	texture_->close();
	delete texture_; texture_ = nullptr;
	delete rect_; rect_ = nullptr;
}

void Sprite::render(GameObject * o, Uint32 deltaTime) {
	rect_->x = o->getPosition().getX();
	rect_->y = o->getPosition().getY();
	rect_->w = o->getWidth();
	rect_->h = o->getHeight();

	Game::cameras_[cam_]->renderTexture(texture_, *rect_,
					(SDL_Rect*)nullptr, o->getRotation());
}

void Sprite::setCamera(cameraType cam) {
	cam_ = cam;
}
