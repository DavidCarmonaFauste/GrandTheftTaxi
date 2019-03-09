#include "GameObject.h"

GameObject::GameObject() :
	GameObject(nullptr) {
}

GameObject::GameObject(Game * game) : game_(game),
active_(true),
width_(),
height_(),
position_()
{
}


GameObject::~GameObject() {
}

Game * GameObject::getGame() const
{
	return game_;
}

void GameObject::setGame(Game* game) {
	game_ = game;
}

bool GameObject::isActive() const {
	return active_;
}
void GameObject::setActive(bool active) {
	active_ = active;
}

bool GameObject::toggleActive() {
	active_ = !active_;
	return active_;
}

double GameObject::getWidth() const {
	return width_;
}

void GameObject::setWidth(double width) {
	width_ = width;
}

double GameObject::getHeight() const {
	return height_;
}

void GameObject::setHeight(double height) {
	height_ = height;
}

Vector2D GameObject::getPosition() const {
	return position_;
}

void GameObject::setPosition(const Vector2D &pos) {
	position_.Set(pos.x, pos.y);
}

double GameObject::getRotation() const
{
	return rotation_;
}

void GameObject::setRotation(double angle)
{
	rotation_ = angle;
}

void GameObject::scale(double s) {
	width_ *= s;
	height_ *= s;
}

void GameObject::init() {
}
