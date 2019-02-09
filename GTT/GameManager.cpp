#include "GameManager.h"
#include <iostream>


GameManager::GameManager() : Observable(), Observer() {
}

GameManager::~GameManager() {

}

bool GameManager::receiveEvent(Event *e) {
	// cout << e->type;
	return true;
}