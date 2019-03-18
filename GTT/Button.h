#pragma once
#include "Container.h"
#include "Sprite.h"
#include "Resources.h"

class MouseClickIC;

// --------- C A L L B A C K S ---------------
using CallBackOnClick = void ();


class Button : public Container {
public:
	Button (CallBackOnClick cb, Resources::ButtonTypes buttonType);
	virtual ~Button ();

	CallBackOnClick *callback = nullptr;

private:
	Sprite* buttonSprite = nullptr;
	MouseClickIC* mouseClickIC = nullptr;
};

