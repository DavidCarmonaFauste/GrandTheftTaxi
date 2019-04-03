#pragma once
#include "Container.h"
#include "Sprite.h"
#include "Animation.h"
#include "Constants.h"


class MouseClickIC;
class MouseOverObject;

// --------- C A L L B A C K S ---------------
using CallBackOnClick = void ();


class Button : public Container {
public:
	//Button (CallBackOnClick cb, ButtonInfo  buttonType);
	Button(CallBackOnClick cb, ButtonInfo  buttonType, const int col = 1, const int row = 1);
	virtual ~Button ();

	CallBackOnClick *callback = nullptr;

	Animation* getButtonAnimacion();

private:
	//Sprite* buttonSprite = nullptr;
	Animation* buttonAnimation_ = nullptr;
	MouseClickIC* mouseClickIC = nullptr;
	MouseOverObject* mouseOverObj_ = nullptr;
};

