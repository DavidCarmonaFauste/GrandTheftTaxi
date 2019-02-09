#pragma once
#include "Observer.h"

class GameManager :
	public Observable, public Observer {
public:
	GameManager();
	virtual ~GameManager();
};

