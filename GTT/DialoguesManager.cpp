#include "DialoguesManager.h"

unique_ptr<DialoguesManager> DialoguesManager::instance = nullptr;

DialoguesManager::DialoguesManager()
{
	time = 0;
	displaying = false;
	maxTime = 0;
	
	pos = Vector2D(500, 800);
	setPosition(pos);
	font = new Font(FONT_COOLFONT, 60);
	color = SDL_Color();
	color.r = 255; color.g = 255; color.b = 255;
	txt_ = new Text(font, "", color);
	
	txt_->setCamera(UI_CAMERA);
	addRenderComponent(txt_);
	txt_->setAutoPos(true);
	txt_->setAutoSize(false);
	txt_->setSize(600, 80);

	evento(disparo);
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

void DialoguesManager::evento(vector <pair<string, string>> phrases)
{
	if (!displaying) {
		int random = rand() % phrases.size();
		if (english) txt_->setText(phrases[random].second);
		else txt_->setText(phrases[random].first); 
		displaying = true;
		maxTime = timeDialogues;
	}
}

void DialoguesManager::update(int deltaTime)
{
	if (displaying) {

		time += deltaTime;
		if (time > maxTime) {
			txt_->setText(" ");
			displaying = false;
			maxTime = 0;
			time = 0;
		}
		cout << time << endl;
	}
}
