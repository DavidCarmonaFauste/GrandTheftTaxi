#include "DialoguesManager.h"

unique_ptr<DialoguesManager> DialoguesManager::instance = nullptr;

DialoguesManager::DialoguesManager()
{
	time = 0;
	displaying = false;
	maxTime = 0;
	
	pos = Vector2D(200, 200);
	setPosition(pos);
	font = new Font(FONT_COOLFONT, 80);
	color = SDL_Color();
	color.r = 255; color.g = 255; color.b = 255;
	txt_ = new Text(font, "SDFGHJKL", color);
	
	txt_->setCamera(UI_CAMERA);
	addRenderComponent(txt_);
	txt_->setAutoPos(true);
	txt_->setAutoSize(false);
	txt_->setSize(200, 80);

}


DialoguesManager * DialoguesManager::getInstance()
{
	if (this != nullptr) {
		if (instance == nullptr) {
			instance.reset(new DialoguesManager());
		}
		return instance.get();
	}
	else {
		return new DialoguesManager();

	}
}

DialoguesManager::~DialoguesManager()
{
}

void DialoguesManager::eventoDisparo(int time)
{
	
	txt_->setText(disparo[0].first);
	displaying = true;
	maxTime = time; 
}

void DialoguesManager::update(int deltaTime)
{/*
	if (displaying) {
		txt_->render();
		time += deltaTime;
		if (time > maxTime) {
			d->setText("");
			displaying = false;
			maxTime = 0;
			time = 0;
		}
	}*/
}
