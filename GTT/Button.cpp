#include "Button.h"
#include "MouseClickIC.h"

//sprite
/*Button::Button (CallBackOnClick cb, ButtonInfo  buttonType) {
	callback = cb;

	setPosition (Vector2D (buttonType.pos.x, buttonType.pos.y));
	setWidth(500); setHeight(200);

	buttonSprite = new Sprite(buttonType.idlePath); 
	mouseClickIC = new MouseClickIC ();

	addRenderComponent(buttonSprite);
	addInputComponent (mouseClickIC);
}*/

//spriteSheet
Button::Button(CallBackOnClick cb, const vector <ButtonInfo>  buttonType, const soundId sound)
{
	callback = cb;


	mouseClickIC = new MouseClickIC(buttonType);

	buttonAnimation_ = new Animation();
	buttonAnimation_->loadAnimation(buttonType[defaultAnm].idlePath, buttonType[defaultAnm].name, buttonType[defaultAnm].frAnm.cols, buttonType[defaultAnm].frAnm.rows);
	
	addRenderComponent(buttonAnimation_);

	addInputComponent(mouseClickIC);

	clickSound_ = sound;

}


Button::~Button () {
	//delete buttonSprite; buttonSprite = nullptr;
	delete buttonAnimation_; buttonAnimation_ = nullptr;
	delete mouseClickIC; mouseClickIC = nullptr;
}

Animation * Button::getButtonAnimacion()
{
	return buttonAnimation_;
}

bool  Button:: isMouseClickICEvent()
{
	return mouseClickIC->isClickEvent();
}

const soundId Button::getSound()
{
	if (clickSound_ != (int)-1)
		return clickSound_;
	else
		return (soundId)-1;
}
