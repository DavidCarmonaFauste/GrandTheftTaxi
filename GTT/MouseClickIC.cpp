#include "MouseClickIC.h"
#include "Button.h"
#include "Game.h"

MouseClickIC::MouseClickIC (const vector<ButtonInfo> bType, int key) {
	mouseClickKey_ = key;
	clickEvent_ = false;
	buttonType_ = bType; buttonTypeSize_ = (buttonType_.size() -1);
}


MouseClickIC::~MouseClickIC () {
}


void MouseClickIC::handleInput(GameObject * o, Uint32 deltaTime, const SDL_Event & event) {

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
				if (static_cast<Button*>(o)->getButtonAnimacion() != nullptr) {
					//asegura que el vector de struc buttonInfo tiene una componente para la animación 
					if (buttonTypeSize_ >= (int)clickButton) {
						static_cast<Button*>(o)->getButtonAnimacion()->loadAnimation(buttonType_[clickButton].idlePath, buttonType_[clickButton].name, buttonType_[clickButton].frAnm.cols, buttonType_[clickButton].frAnm.rows);
							static_cast<Button*>(o)->getButtonAnimacion()->playAnimation(buttonType_[clickButton].name, 24.0f, false);
					}
					
				}
				//notifica al update del Estado que el evento se ha producido. y el estado llama a su callback
				clickEvent_ = true;
			}

		}

	}//SDL_MOUSEBUTTONUP
	else {
		if (!clickEvent_) {
			if (event.type == SDL_MOUSEMOTION) {
				//si el puntero se encuentra dentro del rango del GO
				if (mouseX > int(objPosition.x) &&
					mouseX < int(objPosition.x + o->getWidth()) &&
					mouseY > int(objPosition.y) &&
					mouseY < int(objPosition.y + o->getHeight())) {
					if (static_cast<Button*>(o)->getButtonAnimacion() != nullptr) {
						if (buttonTypeSize_ >= (int)overButton) {
							static_cast<Button*>(o)->getButtonAnimacion()->loadAnimation(buttonType_[overButton].idlePath, buttonType_[overButton].name, buttonType_[overButton].frAnm.cols, buttonType_[overButton].frAnm.rows);
						}
						
					}
				}
				else {
					if (static_cast<Button*>(o)->getButtonAnimacion() != nullptr) {
						static_cast<Button*>(o)->getButtonAnimacion()->loadAnimation(buttonType_[defaultAnm].idlePath, buttonType_[defaultAnm].name, buttonType_[defaultAnm].frAnm.cols, buttonType_[defaultAnm].frAnm.rows);
					}
				}
			}//SDL_MOUSEMOTION
		}
	}
}



bool MouseClickIC:: isClickEvent()
{
	return clickEvent_;
}
