#include "MouseClickIC.h"
#include "Button.h"
#include "Game.h"

MouseClickIC::MouseClickIC(int key) {
	mouseClickKey_ = key;	
}


MouseClickIC::~MouseClickIC () {}


void MouseClickIC::handleInput(GameObject * o, Uint32 deltaTime, const SDL_Event & event) {

	Button* button = static_cast<Button*>(o);

	if (button != nullptr) {
		//Se recoge las coord. de pos. para activar la animacion overObj si no se pulsa el boton izq raton
		int mouseX, mouseY;
		SDL_GetMouseState(&mouseX, &mouseY);
		int winW = Game::getInstance()->getWindowWidth();
		int camW = Game::getInstance()->getCameraWidth();
		int winH = Game::getInstance()->getWindowHeight();
		int camH = Game::getInstance()->getCameraHeight();

		mouseX = (float(mouseX) / float(winW)) * camW;
		mouseY = (float(mouseY) / float(winH)) * camH;

		Vector2D objPosition = o->getPosition();

		if (event.type == SDL_MOUSEBUTTONUP) {

			//si el puntero se encuentra dentro del rango del GO
			if (mouseX > int(objPosition.x) &&
				mouseX < int(objPosition.x + o->getWidth()) &&
				mouseY > int(objPosition.y) &&
				mouseY < int(objPosition.y + o->getHeight())) {

				//si se produce el evento de input leftMouse
				if (event.button.button == mouseClickKey_) {
					MouseClickLeft e(this, button->getIndex());
					broadcastEvent(e);									
				}
			}
		}//SDL_MOUSEBUTTONUP

		else {
			if (event.type == SDL_MOUSEMOTION) {
				//si el puntero se encuentra dentro del rango del GO
				if (mouseX > int(objPosition.x) &&
					mouseX < int(objPosition.x + o->getWidth()) &&
					mouseY > int(objPosition.y) &&
					mouseY < int(objPosition.y + o->getHeight())) {

					MouseOverObj e(this, button->getIndex());
					broadcastEvent(e);

				}
				else {
					NotMouseOverObj e(this, button->getIndex());
					broadcastEvent(e);
				}
			}//SDL_MOUSEMOTION
		}
	}
}

