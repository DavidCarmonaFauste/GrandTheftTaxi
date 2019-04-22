#include "DialoguesManager.h"



DialoguesManager::DialoguesManager()
{
}


DialoguesManager::~DialoguesManager()
{
}

void DialoguesManager::eventoDisparo(int time)
{
	Font* font = new Font(FONT_LATO, 60);
	SDL_Color color =  SDL_Color({ 1,1,1,1 });
	d = new Dialogues(font,disparo[0].first,color,Vector2D(200,200),100,50);
	displaying = true;
	maxTime = time;
}

void DialoguesManager::update(int deltaTime)
{
	if (displaying) {
		time += deltaTime;
		if (time > maxTime) {
			delete d;
			d = nullptr;
			displaying = false;
			maxTime = 0;
			time = 0;
		}
	}
}
