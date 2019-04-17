#pragma once
#include "Text.h"

class Dialogues
{
public:
	Dialogues(Sprite box,Sprite character,Font* font, string text = "", SDL_Color color = SDL_Color());
	~Dialogues();

	void setText(string txt);

private:
	Text* text_;
	Sprite box_,character_;
	
};

