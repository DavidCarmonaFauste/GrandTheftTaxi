#include "MouseOverObject.h"



MouseOverObject::MouseOverObject()
{
}


MouseOverObject::~MouseOverObject()
{
}


void MouseOverObject::handleInput(GameObject * o, Uint32 deltaTime, const SDL_Event & event) {
	if (event.type == SDL_MOUSEBUTTONUP) {
		/*if (event.button.button == mouseClickKey_) {
			int mouseX, mouseY;
			SDL_GetMouseState(&mouseX, &mouseY);
			int winW = Game::getInstance()->getWindowWidth();
			int camW = Game::getInstance()->getCameraWidth();
			int winH = Game::getInstance()->getWindowHeight();
			int camH = Game::getInstance()->getCameraHeight();

			mouseX = (float(mouseX) / float(winW)) * camW;
			mouseY = (float(mouseY) / float(winH)) * camH;

			Vector2D objPosition = o->getPosition();


			if (mouseX > int(objPosition.x) &&
				mouseX < int(objPosition.x + o->getWidth()) &&
				mouseY > int(objPosition.y) &&
				mouseY < int(objPosition.y + o->getHeight())) {
				static_cast<Button*>(o)->callback();
			}
		}*/
	}
}