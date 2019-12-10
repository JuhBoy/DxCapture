#pragma once
#ifndef CDXCAPTRE
#define CDXCAPTRE

#pragma comment(lib, "dxgi.lib")

#include <d3d.h>
#include <dxgi1_2.h>
#include <dxgi.h>
#include <vector>

class DxCapture
{
public:
	DxCapture();
	~DxCapture();

	DxCapture(const DxCapture& original) = delete;

	void capture();
private:
	IDXGIFactory* factoryPtr;

	unsigned int frameTimeout;
	int x;
	int y;

	void initIDXGIFactory();
	std::vector<IDXGIAdapter*> getAdapters();
};


extern "C" __declspec(dllexport) HRESULT createCDxCapture(DxCapture** capture) {
	*capture = new DxCapture();
	return S_OK;
}

#endif // !CDXCAPTRE