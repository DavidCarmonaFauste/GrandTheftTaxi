#pragma once
#include "Text.h"

class Dialogues
{
public:
	Dialogues(Font* font, string text, SDL_Color color, Vector2D pos, int w, int h);
	~Dialogues();

	void setText(string txt);
	void render();

private:
	Text* text_;
	Vector2D pos_;
	int w_, h_;
};

