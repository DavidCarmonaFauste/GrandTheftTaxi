#pragma once
#include "Container.h"
#include "Bridge.h"

class BridgeManager : public Container {
	//hide copyBuilder and 	assignment operator
	BridgeManager(BridgeManager&) = delete;
	BridgeManager & operator=(const BridgeManager &) = delete;

	static unique_ptr<BridgeManager> instance_; //ptr instance class
public:
	virtual ~BridgeManager ();
	void setBridge (Bridge* bridge);

	//init singleton class
	inline static void initInstance() {
		if (instance_.get() == nullptr) {
			instance_.reset(new BridgeManager());
		}
	}
	//get singleton class
	inline static BridgeManager* getInstance() {
		//SDL_assert(instance_.get() != nullptr); //lanza una mensaje con la primera llamada a getInstance, porque devuelve null
		return instance_.get();
	}

	inline static void destroyInstance() {
		instance_.reset();
		instance_.release();
	}

private:
	BridgeManager ();
	Bridge *bridge_ = nullptr;
};

