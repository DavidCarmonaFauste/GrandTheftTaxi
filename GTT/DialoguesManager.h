#pragma once
#include "Dialogues.h"
#include "Phrases.h"
#include "Constants.h"
#include "Text.h"
#include "Container.h"
#include <memory>
#include <math.h>

class DialoguesManager :
	public Container
{
	static unique_ptr<DialoguesManager> instance;
public:
	DialoguesManager* getInstance();
	~DialoguesManager();
	void evento(vector <pair<string, string>> phrases);
	void update(int deltaTime);
	DialoguesManager();

private:
	
	int time;
	Text* txt_;
	bool english = true;
	bool displaying;
	int maxTime;
	Font* font;
	SDL_Color color;
	Vector2D pos;
	int w, h;
	int timeDialogues = 10000;
};

