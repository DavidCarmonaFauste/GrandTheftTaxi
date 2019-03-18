#include "Button.h"
#include "MouseClickIC.h"


Button::Button (CallBackOnClick cb, Resources::ButtonTypes buttonType) {
	callback = cb;

	setPosition (Vector2D (BUTTON_X_POSITION, BUTTON_Y_POSITIONS[int (buttonType)]));
	setWidth(500); setHeight(200);

	buttonSprite = new Sprite(PATH_BUTTONS[int(buttonType)]);
	mouseClickIC = new MouseClickIC ();

	addRenderComponent(buttonSprite);
	addInputComponent (mouseClickIC);
}


Button::~Button () {
	delete buttonSprite; buttonSprite = nullptr;
	delete mouseClickIC; mouseClickIC = nullptr;
}
