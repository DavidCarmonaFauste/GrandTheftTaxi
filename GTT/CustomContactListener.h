#pragma once
#include <Box2D/Box2D.h>

class CustomContactListener : public b2ContactListener {
public:
	CustomContactListener() {};
	~CustomContactListener() {};

	// DO NOT CALL, THIS IS ONLY USED BY BOX2D TO FIRE EVENTS
	virtual void BeginContact(b2Contact* contact) override {
		beginCallback_(contact);
	}

	// DO NOT CALL, THIS IS ONLY USED BY BOX2D TO FIRE EVENTS
	virtual void EndContact(b2Contact* contact) override {
		endCallback_(contact);
	}

	void setBeginCallback(void(*beginCallback)(b2Contact* contact)) { beginCallback_ = beginCallback; };
	void setEndCallback(void(*endCallback)(b2Contact* contact)) { endCallback_ = endCallback; };

private:
	void (*beginCallback_)(b2Contact* contact);
	void (*endCallback_)(b2Contact* contact);
};

