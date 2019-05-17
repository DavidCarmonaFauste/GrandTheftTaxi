#include "BridgeManager.h"

unique_ptr<BridgeManager> BridgeManager::instance_ = nullptr;

BridgeManager::BridgeManager () {
}


BridgeManager::~BridgeManager () {
	delete bridge1_;
	delete bridge2_;
}

void BridgeManager::setBridge (Bridge * bridge, char level) {
	if (level == '1')
		bridge1_ = bridge;
	else
		bridge2_ = bridge;
}
