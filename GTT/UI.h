#pragma once
#include "HealthDisplay.h"
#include "CameraType.h"
#include "Observer.h"
#include "MoneyDisplay.h"
#include "ReloadingDisplay.h"
#include "AmmoDisplay.h"

class UI : public Container, public Observer {
public:
	static UI* getInstance();

	virtual void render(Uint32 deltaTime) override;
	virtual void update(Uint32 deltaTime) override;
	virtual void addUIElement(Container* c);

	virtual bool receiveEvent(Event& e) override;

	void setAmmoActive(bool active) const;

private:
	static UI* singleton_;

	UI();
	virtual ~UI();

	vector<GameObject*> UIElements_;

	HealthDisplay* healthDisplay_;
	MoneyDisplay* moneyDisplay_;
	ReloadingDisplay* reloadDisplay_;
	AmmoDisplay* ammoDisplay_;

	Font* font_;
	SDL_Color fontColor_;
};

