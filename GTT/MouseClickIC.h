#pragma once
#include "InputComponent.h"

class MouseClickIC :
	public InputComponent {
public:
	MouseClickIC (const vector<textureInfo>buttonType, int key = SDL_BUTTON_LEFT);

	virtual ~MouseClickIC ();
	virtual void handleInput(GameObject* o, Uint32 deltaTime, const SDL_Event& event);

	bool isClickEvent();

private:
	int mouseClickKey_;
	bool clickEvent_;
	vector <textureInfo> buttonType_;
	int buttonTypeSize_;
};

