#pragma once
#include "Container.h"
#include "HealthDisplay.h"
#include "CameraType.h"
#include "Observer.h"
#include "MoneyDisplay.h"

class UI : public Container, public Observer
{
public:
	UI();
	virtual ~UI();

	virtual void render(Uint32 deltaTime) override;

	virtual bool receiveEvent(Event* e) override;

private:
	vector<GameObject*> UIElements_;

	HealthDisplay* healthDisplay_;
	MoneyDisplay* moneyDisplay_;

	cameraType cam_ = UI_CAMERA;

	Font* font_;
	SDL_Color fontColor_;
};

