#include "DialoguesManager.h"

unique_ptr<DialoguesManager> DialoguesManager::instance = nullptr;

DialoguesManager::DialoguesManager()
{
	time = 0;
	displaying = false;
	maxTime = 0;
	
	pos = Vector2D(600, 800);
	setPosition(pos);
	font = new Font(FONT_COOLFONT, 80);
	color = SDL_Color();
	color.r = 255; color.g = 255; color.b = 255;
	txt_ = new Text(font, "", color);
	
	txt_->setCamera(UI_CAMERA);
	addRenderComponent(txt_);
	txt_->setAutoPos(true);
	txt_->setAutoSize(false);
	txt_->setSize(200, 80);

	eventoDisparo(7000);
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
{
	if (displaying) {

		time += deltaTime;
		if (time > maxTime) {
			txt_ = new Text(font, "", color);
			displaying = false;
			maxTime = 0;
			time = 0;
		}
		cout << time << endl;
	}
}
