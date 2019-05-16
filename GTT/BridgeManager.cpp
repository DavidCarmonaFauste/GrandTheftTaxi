#include "BridgeManager.h"

unique_ptr<BridgeManager> BridgeManager::instance_ = nullptr;

BridgeManager::BridgeManager () {
}


BridgeManager::~BridgeManager () {
	delete bridge_;
}

void BridgeManager::setBridge (Bridge * bridge) {
	if (bridge_ != nullptr)
		delete bridge_;

	bridge_ = bridge;
}
