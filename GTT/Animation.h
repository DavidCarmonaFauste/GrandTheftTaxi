#pragma once

#include <string>
#include <map>
#include "Texture.h"
#include "RenderComponent.h"
#include "Camera.h"

using namespace std;

class Animation : public RenderComponent {
public:
	Animation();
	virtual ~Animation();

	// Animation
	void loadAnimation(string path, string name, int columns = 1, int rows = 1);
	bool animationExists(string name);

	bool isAnyAnimationPlaying();
	bool isAnimationPlaying(string name);

	bool playAnimation(string name, float speed = true, bool loop = true);
	bool stopAnimation();
	bool pauseAnimation();
	bool resumeAnimation();

	virtual void render(GameObject* o, Uint32 deltaTime) override;

	void setCamera(cameraType cam);

private:
	cameraType cam_ = GAME_CAMERA;
	SDL_Rect* destRect;

	map<string, pair<Texture*, SDL_Rect*>> animations;
	string currentAnim = "";
	int currentFrame = 0;
	double elapsedTime = 0;
	int animationRows = 1, animationColumns = 1;

	const float speedMultiplier = 1000;
	float animationSpeed = 1;
	bool paused = false;
	bool animationLoop = true;

	void renderAnimation(GameObject *o, Uint32 deltaTime);
	void resetAnimationValues();
};

void Animation::setCamera(cameraType cam) {
	cam_ = cam;
}