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
	delete texture;
	delete rect;
}

void Sprite::update(double deltaTime) {
	// Rendering
	if (currentAnim_ != "") {
		renderAnimation(deltaTime);
	}
	else {
		texture->render(*rect);
	}
}

// Animation frames are played in order from left to right,
// top to bottom, with the given speed
void Sprite::loadAnimation(string path, string name, int columns, int rows) {
	Texture* animTexture = new Texture(Game::renderer_, path, rows, columns);
	
	SDL_Rect* animRect = new SDL_Rect();
	animRect->h = animTexture->getH() / rows;
	animRect->w = animTexture->getW() / columns;
	animRect->x = animRect->y = 0;

	animations_[name] = pair<Texture*, SDL_Rect*>(animTexture, animRect);
}

bool Sprite::playAnimation(string name, float speed, bool loop, bool reset) {
	if (animationExists(name)) {
		currentAnim_ = name;
		animationSpeed_ = speed;
		animationLoop_ = loop;

		resetAnimationValues();

		animationColumns_ = animations_[name].first->getW() / animations_[name].second->w;
		animationRows_ = animations_[name].first->getH() / animations_[name].second->h;

		return true;
	}

	return false;
}

bool Sprite::isAnyAnimationPlaying() {
	return currentAnim_ != "";
}

// Checks whether the given animation is currently
// playing
bool Sprite::isAnimationPlaying(string name) {
	return currentAnim_ == name;
}


// Pauses the current animation
bool Sprite::pauseAnimation()
{
	if (isAnyAnimationPlaying()) {
		paused_ = true;
		return true;
	}

	return false;
}

// Resumes a paused animation, returns true if
// the animation was paused, false otherwise
bool Sprite::resumeAnimation()
{
	if (isAnyAnimationPlaying() && paused_) {
		paused_ = false;
		return true;
	}

	return false;
}

// Stops the current animation, returns true if
// any animation is playing, false otherwise
bool Sprite::stopAnimation() {
	if (isAnyAnimationPlaying()) {
		currentAnim_ = "";
		return true;
	}

	return false;
}

bool Sprite::animationExists(string name) {
	return animations_.count(name) > 0;
}

void Sprite::renderAnimation(double deltaTime) {
	if (elapsedTime_ > currentFrame_ * speedMultiplier_ / animationSpeed_) {
		currentFrame_++;

		if (currentFrame_ >= animationColumns_ * animationRows_) {
			if (animationLoop_)
				resetAnimationValues();
			else
				currentAnim_ = "";
		}
	}

	Texture* animTexture = animations_[currentAnim_].first;
	SDL_Rect* animRect = animations_[currentAnim_].second;

	animTexture->renderFrame(*animRect, trunc(currentFrame_ / animationColumns_),
								currentFrame_ % animationColumns_);

	if (isAnyAnimationPlaying() && !paused_) elapsedTime_ += deltaTime;
}

void Sprite::resetAnimationValues() {
	paused_ = false;
	elapsedTime_ = 0;
	currentFrame_ = 0;
}

