#pragma once
#include "Container.h"
#include "Sprite.h"
#include "Animation.h"
#include "Constants.h"

class MouseClickIC;

// --------- C A L L B A C K S ---------------
using CallBackOnClick = void ();


class Button : public Container {
public:
	Button (CallBackOnClick cb, ButtonId  buttonType);
	Button(CallBackOnClick cb, ButtonId  buttonType, const int col, const int row);
	virtual ~Button ();

	CallBackOnClick *callback = nullptr;

private:
	Sprite* buttonSprite = nullptr;
	Animation* buttonAnimation_ = nullptr;
	MouseClickIC* mouseClickIC = nullptr;
};

