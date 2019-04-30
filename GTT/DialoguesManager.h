#pragma once
#include "Dialogues.h"
#include "Phrases.h"
#include "Constants.h"
#include <memory>

class DialoguesManager
{
	static unique_ptr<DialoguesManager> instance;
public:
	DialoguesManager* getInstance();
	~DialoguesManager();
	void eventoDisparo(int time);
	void update(int deltaTime);
	DialoguesManager();

private:
	
	int time;
	Dialogues* d;
	bool english = false;
	bool displaying;
	int maxTime;
	Font* font;
	SDL_Color color;
	Vector2D pos;
	int w, h;
};

