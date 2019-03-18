
#pragma once
//#include "Game.h"
#include "Vector2D.h"
#include <SDL.h>
#include "Constants.h"

using namespace std;

class GameObject {

public:
	GameObject();
	//GameObject(Game* game);
	virtual ~GameObject();

	//Game* getGame() const;
	//void setGame(Game* game);

	bool isActive() const;
	void setActive(bool active);
	bool toggleActive();

	double getWidth() const;
	virtual void setWidth(double width);

	double getHeight() const;
	virtual void setHeight(double height);

	void scale(double s);

	Vector2D getPosition() const;

	// If force is set to true, components such as the physics one
	// should set their positions to this
	virtual void setPosition(const Vector2D &pos, bool force = false);

	Vector2D getVelocity() const;
	virtual void setVelocity(const Vector2D &vel);

	Vector2D getAcceleration() const;
	virtual void setAcceleration(const Vector2D &vel);

	double getRotation() const;
	virtual void setRotation(double angle);
	virtual Vector2D getCenter();


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
	//Game* game_; // pointer to the game

	bool active_;   // indicates if the object is active

	double width_;  // width
	double height_; // height

	Vector2D position_; // position (suppose to be left-top corner)
	Vector2D velocity_; // velocity
	Vector2D acceleration_; // acceleration
	double rotation_; // rotation (for the corresponding texture)
};


