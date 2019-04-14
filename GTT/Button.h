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
	Button(CallBackOnClick cb);
	virtual ~Button ();

	CallBackOnClick *callback = nullptr;
	
	void setButtonAnimation(Animation* anm);
	void setMouseClickIC(MouseClickIC* mCIc);
	void setClickSound(soundId = (soundId)-1);

	Animation* getButtonAnimacion();
	bool isMouseClickICEvent();

	const soundId getSound();


private:
	Sprite* buttonSprite_ = nullptr;
	Animation* buttonAnimation_ = nullptr;
	MouseClickIC* mouseClickIC_ = nullptr;

	soundId clickSound_;
};

