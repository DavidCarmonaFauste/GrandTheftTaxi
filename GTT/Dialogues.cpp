#include "Dialogues.h"



Dialogues::Dialogues(Font* font, string text, SDL_Color color,Vector2D pos, int w, int h)
{
	
	text_ = new Text(font, text, color);
	text_->setCamera(UI_CAMERA);
	text_->setAutoPos(true);
	text_->setAutoSize(false);
	text_->setSize(w, h);
	pos_ = pos;
	w_ = w;
	h_ = h;

	
	render();


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

void Dialogues::render()
{
	text_->render(pos_, w_, h_);
}
