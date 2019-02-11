#include "Animation.h"
#include "Game.h"


Animation::Animation()
{
}


Animation::~Animation()
{
}

void Animation::update(double deltaTime) {
	// Rendering
	if (currentAnim != "") {
		renderAnimation(deltaTime);
	}
}


// Animation frames are played in order from left to right,
// top to bottom, with the given speed
void Animation::loadAnimation(string path, string name, int columns, int rows) {
	Texture* animTexture = new Texture(Game::renderer, path, rows, columns);

	SDL_Rect* animRect = new SDL_Rect();
	animRect->h = animTexture->getH() / rows;
	animRect->w = animTexture->getW() / columns;
	animRect->x = animRect->y = 0;

	animations[name] = pair<Texture*, SDL_Rect*>(animTexture, animRect);
}

bool Animation::playAnimation(string name, float speed, bool loop, bool reset) {
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

bool Animation::isAnyAnimationPlaying() {
	return currentAnim != "";
}

// Checks whether the given animation is currently
// playing
bool Animation::isAnimationPlaying(string name) {
	return currentAnim == name;
}


// Pauses the current animation
bool Animation::pauseAnimation()
{
	if (isAnyAnimationPlaying()) {
		paused = true;
		return true;
	}

	return false;
}

// Resumes a paused animation, returns true if
// the animation was paused, false otherwise
bool Animation::resumeAnimation()
{
	if (isAnyAnimationPlaying() && paused) {
		paused = false;
		return true;
	}

	return false;
}

// Stops the current animation, returns true if
// any animation is playing, false otherwise
bool Animation::stopAnimation() {
	if (isAnyAnimationPlaying()) {
		currentAnim = "";
		return true;
	}

	return false;
}

bool Animation::animationExists(string name) {
	return animations.count(name) > 0;
}

void Animation::renderAnimation(double deltaTime) {
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

void Animation::resetAnimationValues() {
	paused = false;
	elapsedTime = 0;
	currentFrame = 0;
}

