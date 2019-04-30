#include "DialoguesManager.h"

unique_ptr<DialoguesManager> DialoguesManager::instance = nullptr;

DialoguesManager::DialoguesManager()
{
	time = 0;
	displaying = false;
	maxTime = 0;

	font = new Font(FONT_LATO, 60);
	color ={ 12,35,34,1 };
	pos = Vector2D(200, 200);
	w = 100;
	h = 50;
	string txt = "";
	d = new Dialogues(font,txt,color,pos,w,h);
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
