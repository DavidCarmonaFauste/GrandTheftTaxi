#pragma once
#include "Game.h"
#include "Vector2D.h"
#include <SDL.h>
using namespace std;

class GameObject	{

public:
	GameObject();
	GameObject(Game* game);
	virtual ~GameObject();

	Game* getGame() const;
	void setGame(Game* game);

	bool isActive() const;
	void setActive(bool active);
	bool toggleActive();

	double getWidth() const;
	void setWidth(double width);

	double getHeight() const;
	void setHeight(double height);

	void scale(double s);

	Vector2D getPosition() const;
	void setPosition(const Vector2D &pos);

	double getRotation() const;
	void setRotation(double angle);

	// some GameObjects cannot be initialized in the constructor,
	// for example when we create them using the default constructor
	// and without passing the game. This method is supposed to
	// be called once they are ready to be initialized. The
	// default implementation does nothing.
	virtual void init();

	// abstract methods to be implemented in sub-classes
	virtual void handleInput(Uint32 deltaTime, const SDL_Event& event) = 0;
	virtual void update(Uint32 deltaTime) = 0;
	virtual void render(Uint32 deltaTime) = 0;

protected:
	Game* game_; // pointer to the game

	bool active_;   // indicates if the object is active

	double width_;  // width
	double height_; // height

	Vector2D position_; // position (suppose to be left-top corner)
	double rotation_; // rotation (for the corresponding texture)
};

