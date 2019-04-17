#include "Dialogues.h"



Dialogues::Dialogues(Sprite box, Sprite character, Font* font, string text, SDL_Color color)
{
	box_ = box;
	character_ = character;
	text_ = new Text(font, text, color);
}


Dialogues::~Dialogues()
{
	delete text_;
	text_ = nullptr;
}

void Dialogues::setText(string txt)
{
	text_->setText(txt);
}
