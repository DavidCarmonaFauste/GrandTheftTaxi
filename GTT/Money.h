#pragma once
#include "Container.h"
#include "Observer.h"


class Money : public Container, public Observable, public Observer {
public:
	static Money* getInstance();

	virtual bool receiveEvent(Event& e) override;

	void setCurrentMoney(int money);
	void setMinMoney(int money);

	int getCurrentMoney();
	int getMinMoney();


private:
	static Money *singleton_;

	Money();
	virtual ~Money();

	int minimumMoney_ = 0;
	int currentMoney_;
};

