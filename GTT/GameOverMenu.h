#pragma once
#include "GameState.h"
#include "Observer.h"
#include "Button.h"

class GameOverMenu :
	public GameState, public Observer, public Observable{
public:
	GameOverMenu();
	virtual ~GameOverMenu();

	virtual void start() override;
	virtual void end() override;
	virtual void updateState();

	virtual void update(Uint32 deltaTime);
	virtual bool receiveEvent(Event& e);
private:
	Container *background_, *blackBackground_;
	Sprite *backgroundSprite_, *blackBackgoundSprite_;

	map<string, Button*> buttons_;
	Sprite *backSprite_;

	void setBackground();
	void setButtons();
	void setButtonComponents();
};

