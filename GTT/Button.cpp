#include "Button.h"
#include "MouseClickIC.h"
#include "MouseOverObject.h"

//sprite
Button::Button (CallBackOnClick cb, ButtonId  buttonType) {
	callback = cb;

	setPosition (Vector2D (BUTTON_X_POSITION, BUTTON_Y_POSITIONS[int (buttonType)]));
	setWidth(500); setHeight(200);

	buttonSprite = new Sprite(PATH_BUTTONS[int(buttonType)]); 
	mouseClickIC = new MouseClickIC ();

	addRenderComponent(buttonSprite);
	addInputComponent (mouseClickIC);
}

//spriteSheet
Button::Button(CallBackOnClick cb, ButtonId  buttonType, const int col, const int row)
{
	callback = cb;

	setPosition(Vector2D(BUTTON_X_POSITION, BUTTON_Y_POSITIONS[int(buttonType)]));
	setWidth(500); setHeight(200);

	mouseClickIC = new MouseClickIC();
	mouseOverObj_ = new MouseOverObject();

	buttonAnimation_ = new Animation();
	buttonAnimation_->loadAnimation(PATH_BUTTONS[int(buttonType)], ButtonsNames_.at(buttonType), col, row);
	addRenderComponent(buttonAnimation_);
	addInputComponent(mouseClickIC);
	addInputComponent(mouseOverObj_);

}


Button::~Button () {
	delete buttonSprite; buttonSprite = nullptr;
	delete buttonAnimation_; buttonAnimation_ = nullptr;
	delete mouseClickIC; mouseClickIC = nullptr;
	delete mouseOverObj_; mouseOverObj_ = nullptr;
}
