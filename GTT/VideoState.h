#pragma once
#include "GameState.h"
#include <dshow.h> //gestiona la reproducción de vídeo y adudio para la lectrua de fichero 
#include <string>



class VideoState :
	public GameState
{
public:
	VideoState(string s) : s_(s) {videoInit();}

	~VideoState(){}

	void videoInit() {
		hr = CoCreateInstance(CLSID_FilterGraph, NULL, CLSCTX_INPROC_SERVER, IID_IGraphBuilder, (void **)& pGraph);
		hr = pGraph->QueryInterface(IID_IMediaControl, (void **)&pControl);
		hr = pGraph->QueryInterface(IID_IMediaEvent, (void **)&pEvent);
	}

	int loadVideoFile(string s) {
		wstring widestr = wstring(s.begin(), s.end());
		const wchar_t* szName = widestr.c_str();
		hr = pGraph->RenderFile(szName, NULL);

		if (hr != NULL) {
			hr = pControl->Run();
			return 0;
		}
		else { return -1; }
	}


private:
	string s_;
	IGraphBuilder *pGraph;
	HRESULT hr;
	
	IMediaControl *pControl;
	IMediaEvent   *pEvent;
	
};

