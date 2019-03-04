#pragma once
#include "Container.h"


class CursorLC;
class Animation;

class Reticule :public Container
{
public:
	Reticule();
	virtual ~Reticule();
	virtual void ChangeReticule(string ret);

private:
	map<string, string> animations_;
	Animation* animC_;
	CursorLC* cursorC_;

};

