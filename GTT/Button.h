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
	Button(CallBackOnClick cb, ButtonInfo  buttonType);
	virtual ~Button ();

	CallBackOnClick *callback = nullptr;
	
	Animation* getButtonAnimacion();
	bool isMouseClickICEvent();



private:
	//Sprite* buttonSprite = nullptr;
	Animation* buttonAnimation_ = nullptr;
	MouseClickIC* mouseClickIC = nullptr;
	MouseOverObject* mouseOverObj_ = nullptr;
};

