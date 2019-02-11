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

	void update(double deltaTime);

	// Animation
	void loadAnimation(string path, string name, int columns = 1, int rows = 1);
	bool animationExists(string name);

	bool isAnyAnimationPlaying();
	bool isAnimationPlaying(string name);

	bool playAnimation(string name, float speed = true, bool loop = true, bool reset = true);
	bool stopAnimation();
	bool pauseAnimation();
	bool resumeAnimation();

private:
	Texture *texture;
	SDL_Rect *rect;

	// Animation
	map<string, pair<Texture*, SDL_Rect*>> animations;
	string currentAnim = "";
	int currentFrame = 0;
	double elapsedTime = 0;
	int animationRows = 1, animationColumns = 1;

	const float speedMultiplier = 1000;
	float animationSpeed = 1;
	bool paused = false;
	bool animationLoop = true;

	void renderAnimation(double deltaTime);
	void resetAnimationValues();
};
