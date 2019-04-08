#pragma once
#include "GameState.h"
#include "UI.h"
#include "Money.h"
#include "Button.h"

class ShopState : public GameState {
public:
	ShopState();
	virtual ~ShopState();

	virtual void start() override;
	virtual void end() override;

	virtual void update(Uint32 deltaTime) override;
	virtual void handleEvents(Uint32 deltaTime, SDL_Event& event) override;

private:
	Button* refillButton_;

	static void refillCallback();
};

