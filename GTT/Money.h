#pragma once
#include "Container.h"
#include "Observer.h"


class Money : public Container, public Observable, public Observer {
public:
	Money();
	virtual ~Money();

	virtual bool receiveEvent(Event& e) override;

	void setCurrentMoney(int money);
	void setMinMoney(int money);

	int getCurrentMoney();
	int getMinMoney();


private:
	int minimumMoney_ = 0;
	int currentMoney_;
};

