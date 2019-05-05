#include "DialoguesManager.h"

unique_ptr<DialoguesManager> DialoguesManager::instance = nullptr;

DialoguesManager::DialoguesManager()
{
	time = 0;
	displaying = false;
	maxTime = 0;

	font = new Font(FONT_COOLFONT, 80);
	color = SDL_Color();
	color.r = 255; color.g = 255; color.b = 255;
	txt_ = new Text(font, "SDFGHJKL", color);
	pos = Vector2D(200, 200);
	w = 100;
	h = 50;
	string txt = "";
	d = new Dialogues(font,txt,color,pos,w,h);

	/*
	setPosition(Vector2D(Game::getInstance()->getCamera(UI_CAMERA)->getWidth()*0.05, Game::getInstance()->getCamera(UI_CAMERA)->getHeight()*0.9));
	SDL_Color fontColor = SDL_Color();
	fontColor.r = 255; fontColor.g = 255; fontColor.b = 255;
	Font* f = new Font(FONT_COOLFONT, 80);
	currentAmmo_ = new Text(f, "", fontColor);
	currentAmmo_->setCamera(UI_CAMERA);
	addRenderComponent(currentAmmo_);
	currentAmmo_->setAutoPos(true);
	currentAmmo_->setAutoSize(false);
	currentAmmo_->setSize(100, 40);
	*/
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
	
	d->setText(disparo[0].first);
	displaying = true;
	maxTime = time; 
}

void DialoguesManager::update(int deltaTime)
{
	if (displaying) {
		d->render();
		time += deltaTime;
		if (time > maxTime) {
			d->setText("");
			displaying = false;
			maxTime = 0;
			time = 0;
		}
	}
}
