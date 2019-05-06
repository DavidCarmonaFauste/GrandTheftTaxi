#include "GameManager.h"



GameManager::GameManager()
{
	initTime = SDL_GetTicks() / 1000;
}


GameManager::~GameManager()
{
}

void GameManager::update(Uint32 deltaTime)
{
	time = (SDL_GetTicks() -initTime) / 1000;

	/*for (auto e : enemies_) {
		if (e.second != nullptr)
			e.second->update(deltaTime);
	}*/
}

