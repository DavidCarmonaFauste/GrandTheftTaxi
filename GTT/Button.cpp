#include "Button.h"
#include "MouseClickIC.h"


//spriteSheet
Button::Button(CallBackOnClick cb)
{
	callback = cb;

	/*mouseClickIC = new MouseClickIC(buttonType);
	buttonAnimation_ = new Animation();
	buttonAnimation_->loadAnimation(buttonType[defaultAnm].idlePath, buttonType[defaultAnm].name, buttonType[defaultAnm].frAnm.cols, buttonType[defaultAnm].frAnm.rows);	
	addRenderComponent(buttonAnimation_);
	addInputComponent(mouseClickIC);*/

}


Button::~Button () {
	if (buttonSprite_ != nullptr) { delete buttonSprite_; buttonSprite_ = nullptr; }
		
	if (buttonAnimation_ !=nullptr){ delete buttonAnimation_; buttonAnimation_ = nullptr; }
		
	if (mouseClickIC_ != nullptr) { delete mouseClickIC_; mouseClickIC_ = nullptr; }
	
}

Animation * Button::getButtonAnimacion()
{
	return buttonAnimation_;
}

void Button::setButtonAnimation(Animation * anm)
{
	buttonAnimation_ = anm;
}

void Button::setMouseClickIC(MouseClickIC * mCIc)
{
	mouseClickIC_ = mCIc;
}

void Button::setClickSound(soundId sound)
{
	clickSound_ = sound;
}

bool  Button:: isMouseClickICEvent()
{
	return mouseClickIC_->isClickEvent();
}

const soundId Button::getSound()
{
	if (clickSound_ != (int)-1)
		return clickSound_;
	else
		return (soundId)-1;
}
