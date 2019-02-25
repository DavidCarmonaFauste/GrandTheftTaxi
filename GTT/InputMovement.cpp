#include "InputMovement.h"



InputMovement::InputMovement(Resources::KeyBindingsId id, PhysicObject* p)
{
	p_ = p;
	k_ = &Resources::keyBindings_[id];
	throttle_ = false;
}


InputMovement::~InputMovement()
{
}

void InputMovement::handleInput(GameObject * o, Uint32 deltaTime, const SDL_Event & event)
{
	/*if (event.type == SDL_KEYDOWN) 
	{
		if (event.key.keysym.sym == k_->forward) 
		{
			throttle_ = true;
		}

		if (event.key.keysym.sym == k_->backwards) {
			
		}
		if (event.key.keysym.sym == SDLK_RIGHT) if (isMoving_()) steeringWheel("R");
		if (event.key.keysym.sym == SDLK_LEFT) if (isMoving_()) steeringWheel("L");
		if (event.key.keysym.sym == SDLK_SPACE) handBrake_ = true;
	}
	else if (event.type == SDL_KEYUP) {
		if (event.key.keysym.sym == SDLK_UP) throttle_ = false;
		if (event.key.keysym.sym == SDLK_SPACE) {
			double rotationRadiant = (rotation_ * 3.14) / 180.0;
			handBrake_ = false;
			if (rotation_ <= 180) dir_.setX(abs(sin(rotationRadiant) * 2));
			else dir_.setX(-abs(sin(rotationRadiant) * 2));
			if (rotation_ >= 90 && rotation_ <= 270)dir_.setY(abs(cos(rotationRadiant) * 2));
			else dir_.setY(-abs(cos(rotationRadiant) * 2));
		}
	}*/
}
