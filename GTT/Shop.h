#pragma once
#include "Container.h"

class Shop : public Container {
public:
	static Shop* getInstance();

	vector<Container*> getTriggers();

private:
	static Shop* singleton_;

	Shop();
	virtual ~Shop();

	vector<Container*> triggers_;
};

