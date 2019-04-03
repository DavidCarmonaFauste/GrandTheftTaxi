#include "MouseClickIC.h"
#include "Button.h"
#include "Game.h"

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
					//static_cast<Button*>(o)->getButtonAnimacion()->setAnimationCol(NEW_GAME_BUTTON.anim_click_frame.col);
					//static_cast<Button*>(o)->getButtonAnimacion()->setAnimationRow(NEW_GAME_BUTTON.anim_click_frame.row);
					static_cast<Button*>(o)->getButtonAnimacion()->setCurrentFrame(1);
					static_cast<Button*>(o)->getButtonAnimacion()->playAnimation(NEW_GAME_BUTTON.name);
					SDL_Delay(2000);

				}
				static_cast<Button*>(o)->callback ();
			}
		}
	}
}
