#include <string>
#include "GameState.h"
#include <dshow.h>
#include <SDL_syswm.h>


#pragma once




class VideoState : public GameState
{
public:

	

	VideoState(const string &s) :s_(s) {
		init();
	}
	~VideoState() {}

	virtual void init() {
		// Initialize the COM library.
		HRESULT hr = CoInitialize(NULL);
		if (FAILED(hr))
		{
			printf("ERROR - Could not initialize COM library");
			return;
		}

		// Create the filter graph manager and query for interfaces. CLSID_FilterGraph
		hr = CoCreateInstance(CLSID_FilterGraph, NULL, CLSCTX_INPROC_SERVER,
			IID_IGraphBuilder, (void **)&pGraph);
		if (FAILED(hr))
		{
			printf("ERROR - Could not create the Filter Graph Manager.");
			return;
		}


		hr = pGraph->QueryInterface(IID_IMediaControl, (void **)&pControl);
		hr = pGraph->QueryInterface(IID_IMediaEvent, (void **)&pEvent);


		// Build the graph. IMPORTANT: Change this string to a file on your system.
		wstring widestr = wstring(s_.begin(), s_.end());
		const wchar_t* szName = widestr.c_str();

		hr = pGraph->RenderFile(szName, NULL);
		if (SUCCEEDED(hr))
		{
			// Run the graph.
			hr = pControl->Run();

			if (SUCCEEDED(hr))
			{
				// Wait for completion.
				long evCode;
				pEvent->WaitForCompletion(INFINITE, &evCode);
			}
		}

		pControl->Release();
		pEvent->Release();
		pGraph->Release();
		CoUninitialize();
	}



protected:
	IGraphBuilder *pGraph = NULL;
	IMediaControl *pControl = NULL;
	IMediaEvent   *pEvent = NULL;

	

private:
	string s_;
};

