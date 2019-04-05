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
Button::Button(CallBackOnClick cb, ButtonInfo  buttonType)
{
	callback = cb;

	setPosition(Vector2D(buttonType.pos.x, buttonType.pos.y));
	setWidth(500); setHeight(200);

	mouseClickIC = new MouseClickIC();

	buttonAnimation_ = new Animation();
	buttonAnimation_->loadAnimation(buttonType.idlePath[defaultAnm], buttonType.name[defaultAnm], buttonType.frAnm[defaultAnm].cols, buttonType.frAnm[defaultAnm].rows);
	
	addRenderComponent(buttonAnimation_);

	addInputComponent(mouseClickIC);

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
