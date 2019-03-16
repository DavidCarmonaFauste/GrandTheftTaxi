#pragma once
#include "Container.h"
#include "HealthDisplay.h"
#include "CameraType.h"
#include "Observer.h"

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

	cameraType cam_ = UI_CAMERA;
};

