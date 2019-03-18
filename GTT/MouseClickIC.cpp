#include "MouseClickIC.h"
#include "Button.h"


MouseClickIC::MouseClickIC (int key) {
	mouseClickKey_ = key;
}


MouseClickIC::~MouseClickIC () {
}


void MouseClickIC::handleInput (GameObject * o, Uint32 deltaTime, const SDL_Event & event) {
	if (event.type == SDL_MOUSEBUTTONUP) {
		if (event.button.button == mouseClickKey_) {
			int mouseX, mouseY;
			SDL_GetMouseState (&mouseX, &mouseY);
			mouseX = (float(mouseX) / float(WIN_WIDTH)) * CAMERA_WIDTH;
			mouseY = (float(mouseY) / float(WIN_HEIGHT)) * CAMERA_HEIGHT;

			Vector2D objPosition = o->getPosition ();
			

			if (mouseX > int (objPosition.getX ()) &&
			mouseX < int (objPosition.getX () + o->getWidth()) &&
			mouseY > int (objPosition.getY ()) &&
			mouseY < int (objPosition.getY () + o->getHeight())) {
				static_cast<Button*>(o)->callback ();
			}
		}
	}
}
