#pragma once

#include <SDL.h>
#include <string>

using namespace std;
typedef unsigned int uint;

class VideoState
{
public:
	VideoState(string s){
		videoPath_ = s;
	}

	~VideoState(){}

	virtual void videoInit() = 0;


protected:
	string videoPath_;

private:
	
};

