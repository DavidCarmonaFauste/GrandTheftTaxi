#pragma once
#include "Trigger.h"

class Bridge : public Trigger {
public:
	Bridge (int w, int h, int x, int y);
	virtual ~Bridge ();

protected:
	virtual void beginCallback(b2Contact *contact) override;
	virtual void endCallback(b2Contact *contact) override;
};

