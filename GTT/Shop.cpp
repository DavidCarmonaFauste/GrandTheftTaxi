#include "Shop.h"

Shop* Shop::singleton_ = nullptr;
Shop * Shop::getInstance() {
	if (singleton_ == nullptr)
		singleton_ = new Shop();
	return singleton_;
}

vector<Container*> Shop::getTriggers() {
	return triggers_;
}

Shop::Shop() {

}

Shop::~Shop() {

}
