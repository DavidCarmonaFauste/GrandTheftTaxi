#pragma once
#include "Dialogues.h"
#include "Phrases.h"
#include "Constants.h"

class DialoguesManager
{
public:
	DialoguesManager();
	~DialoguesManager();
	void eventoDisparo(int time);
	void update(int deltaTime);

private:
	int time = 0;
	Dialogues* d = nullptr;
	bool english = false;
	bool displaying = false;
	int maxTime = 0;
};

