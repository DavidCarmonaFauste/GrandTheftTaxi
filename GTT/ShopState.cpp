#include "ShopState.h"



ShopState::ShopState() {
	// UI
	UI::getInstance()->setAmmoActive(false);
	stage_.push_back(UI::getInstance());
}


ShopState::~ShopState() {

}

void ShopState::start() {
	UI::getInstance()->setAmmoActive(false);
}

void ShopState::end() {
	UI::getInstance()->setAmmoActive(true);
}

void ShopState::handleEvents(Uint32 deltaTime, SDL_Event & event) {
	GameState::handleEvents(deltaTime, event);

	if (event.type == SDL_KEYDOWN) {
		if (event.key.keysym.sym == DEFAULT_KEYS.mainMenu) {
			Game::getInstance()->setState(NAME_MAIN_STATE);
		}
	}
}
