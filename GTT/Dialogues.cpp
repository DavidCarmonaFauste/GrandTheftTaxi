#include "Dialogues.h"



Dialogues::Dialogues(Font* font, string text, SDL_Color color,Vector2D pos, int w, int h)
{
	
	text_ = new Text(font, text, color);
	
	

	
	text_->render(pos,w,h);


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
