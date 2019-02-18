#pragma once

#include <list>
#include <SDL.h>
#include "GameObject.h"


class GameState
{

protected:
	list<GameObject*> stage_;

private:
	


public:
	GameState(){}
	~GameState(){}

	virtual void update(Uint32 deltaTime) { for (GameObject* o : stage_) o->update(deltaTime); }

	virtual bool handleEvents(Uint32 deltaTime, SDL_Event& event) {
		bool e = false; //variable de control
		if (!stage_.empty()) {
			auto it = stage_.begin();
			//se recorre la lista, se comunica con la función correspondiente, si hay evento rompe el ciclo actual.
			while (!e && it != stage_.end()) {
				if ((*it)->handleInput(deltaTime, event))
					e = true;
				else
					it++;
			}
		}
		return e;
	}
	virtual void render(Uint32 deltaTime) const { for (GameObject* o : stage_) o->render(deltaTime); }

};

