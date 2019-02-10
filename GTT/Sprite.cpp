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
	// Rendering
	if (currentAnim != "") {
		renderAnimation(deltaTime);
	}
	else {
		texture->render(*rect);
	}
}

// Animation frames are played in order from left to right,
// top to bottom, with the given speed
void Sprite::loadAnimation(string path, string name, int columns, int rows) {
	Texture* animTexture = new Texture(Game::renderer, path, rows, columns);
	
	SDL_Rect* animRect = new SDL_Rect();
	animRect->h = animTexture->getH() / rows;
	animRect->w = animTexture->getW() / columns;
	animRect->x = animRect->y = 0;

	animations[name] = pair<Texture*, SDL_Rect*>(animTexture, animRect);
}

bool Sprite::playAnimation(string name, float speed, bool loop, bool reset) {
	if (animationExists(name)) {
		currentAnim = name;
		animationSpeed = speed;
		animationLoop = loop;

		resetAnimationValues();

		animationColumns = animations[name].first->getW() / animations[name].second->w;
		animationRows = animations[name].first->getH() / animations[name].second->h;

		return true;
	}

	return false;
}

bool Sprite::isAnyAnimationPlaying() {
	return currentAnim != "";
}

// Checks whether the given animation is currently
// playing
bool Sprite::isAnimationPlaying(string name) {
	return currentAnim == name;
}


// Pauses the current animation
bool Sprite::pauseAnimation()
{
	if (isAnyAnimationPlaying()) {
		paused = true;
		return true;
	}

	return false;
}

// Resumes a paused animation, returns true if
// the animation was paused, false otherwise
bool Sprite::resumeAnimation()
{
	if (isAnyAnimationPlaying() && paused) {
		paused = false;
		return true;
	}

	return false;
}

// Stops the current animation, returns true if
// any animation is playing, false otherwise
bool Sprite::stopAnimation() {
	if (isAnyAnimationPlaying()) {
		currentAnim = "";
		return true;
	}

	return false;
}

bool Sprite::animationExists(string name) {
	return animations.count(name) > 0;
}

void Sprite::renderAnimation(double deltaTime) {
	if (elapsedTime > currentFrame * speedMultiplier / animationSpeed) {
		currentFrame++;

		if (currentFrame >= animationColumns * animationRows) {
			if (animationLoop)
				resetAnimationValues();
			else
				currentAnim = "";
		}
	}

	Texture* animTexture = animations[currentAnim].first;
	SDL_Rect* animRect = animations[currentAnim].second;

	animTexture->renderFrame(*animRect, trunc(currentFrame / animationColumns),
								currentFrame % animationColumns);

	if (isAnyAnimationPlaying() && !paused) elapsedTime += deltaTime;
}

void Sprite::resetAnimationValues() {
	paused = false;
	elapsedTime = 0;
	currentFrame = 0;
}

