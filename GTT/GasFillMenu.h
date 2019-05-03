#pragma once
#include "GameState.h"
#include "Button.h"
#include "Observer.h"

class GasFillMenu : public GameState, public Observer, public Observable {
public:
	GasFillMenu ();
	virtual ~GasFillMenu ();

	virtual void start() override;
	virtual void end() override;

	virtual void update(Uint32 deltaTime);
	virtual bool receiveEvent(Event& e);

private:
	Container *background_;
	Sprite *backgroundSprite_;

	map<string, Button*> buttons_;
	Sprite *fill_5_Sprite_, *fill_10_Sprite_, *fill_25_Sprite_, *backSprite_;

	void setBackground ();
	void setButtons ();
	void setButtonComponents ();
};

