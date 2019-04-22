#pragma once
#include "Text.h"

class Dialogues
{
public:
	Dialogues(Font* font, string text, SDL_Color color, Vector2D pos, int, int h);
	~Dialogues();

	void setText(string txt);


private:
	Text* text_;
	
};

