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
	Button(CallBackOnClick cb, const vector <ButtonInfo>  buttonType, const soundId sound = (soundId)-1);
	virtual ~Button ();

	CallBackOnClick *callback = nullptr;
	
	Animation* getButtonAnimacion();
	bool isMouseClickICEvent();

	const soundId getSound();


private:
	//Sprite* buttonSprite = nullptr;
	Animation* buttonAnimation_ = nullptr;
	MouseClickIC* mouseClickIC = nullptr;

	soundId clickSound_;
};

