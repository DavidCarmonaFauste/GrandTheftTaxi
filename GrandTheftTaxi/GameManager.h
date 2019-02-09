#pragma once
#include "Observer.h"

class GameManager :
	public Observable, public Observer {
public:
	GameManager();
	virtual ~GameManager();

	virtual bool GameManager::receiveEvent(Event *e) override;
};

