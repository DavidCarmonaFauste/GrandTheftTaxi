#include "Button.h"
#include "MouseClickIC.h"
#include "MouseOverObject.h"

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
	mouseOverObj_ = new MouseOverObject();

	buttonAnimation_ = new Animation();
	buttonAnimation_->loadAnimation(buttonType.idlePath[defaultFrameButton], buttonType.name, buttonType.frAnm[defaultFrameButton].cols, buttonType.frAnm[defaultFrameButton].rows);
	buttonAnimation_->playAnimation(buttonType.name);
	addRenderComponent(buttonAnimation_);

	addInputComponent(mouseClickIC);
	addInputComponent(mouseOverObj_);

}


Button::~Button () {
	//delete buttonSprite; buttonSprite = nullptr;
	delete buttonAnimation_; buttonAnimation_ = nullptr;
	delete mouseClickIC; mouseClickIC = nullptr;
	delete mouseOverObj_; mouseOverObj_ = nullptr;
}

Animation * Button::getButtonAnimacion()
{
	return buttonAnimation_;
}
