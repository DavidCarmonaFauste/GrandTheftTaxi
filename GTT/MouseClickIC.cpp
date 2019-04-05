#include "MouseClickIC.h"
#include "Button.h"
#include "Game.h"

MouseClickIC::MouseClickIC (int key) {
	mouseClickKey_ = key;
	clickEvent_ = false;
}


MouseClickIC::~MouseClickIC () {
}


void MouseClickIC::handleInput (GameObject * o, Uint32 deltaTime, const SDL_Event & event) {
	if (event.type == SDL_MOUSEBUTTONUP) {
		if (event.button.button == mouseClickKey_) {
			int mouseX, mouseY;
			SDL_GetMouseState (&mouseX, &mouseY);
			int winW = Game::getInstance ()->getWindowWidth ();
			int camW = Game::getInstance ()->getCameraWidth ();
			int winH = Game::getInstance ()->getWindowHeight ();
			int camH = Game::getInstance ()->getCameraHeight ();

			mouseX = (float(mouseX) / float(winW)) * camW;
			mouseY = (float(mouseY) / float(winH)) * camH;

			Vector2D objPosition = o->getPosition ();
			

			if (mouseX > int (objPosition.x) &&
			mouseX < int (objPosition.x + o->getWidth()) &&
			mouseY > int (objPosition.y) &&
			mouseY < int (objPosition.y + o->getHeight())) {

				if (static_cast<Button*>(o)->getButtonAnimacion() != nullptr) {
					static_cast<Button*>(o)->getButtonAnimacion()->loadAnimation(NEW_GAME_BUTTON.idlePath[clickButton], NEW_GAME_BUTTON.name[clickButton], NEW_GAME_BUTTON.frAnm[clickButton].cols, NEW_GAME_BUTTON.frAnm[clickButton].rows);
					static_cast<Button*>(o)->getButtonAnimacion()->playAnimation(NEW_GAME_BUTTON.name[clickButton], 24.0f, false);
					//static_cast<Button*>(o)->callback();
				}	
				clickEvent_ = true;
			}
		}
	}
}

bool MouseClickIC:: isClickEvent()
{
	return clickEvent_;
}
