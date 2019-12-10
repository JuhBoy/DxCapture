#include "dxCapture.h"

DxCapture::DxCapture() : x(0), y(0), frameTimeout(1), factoryPtr(nullptr)
{
}

DxCapture::~DxCapture()
{

}

void DxCapture::initIDXGIFactory()
{
	IDXGIFactory* factory;
	HRESULT hr = CreateDXGIFactory(__uuidof(factory), (void**)&factory);

	if (hr != S_OK) {
		throw 69;
	}

	this->factoryPtr = factory;
}

std::vector<IDXGIAdapter*> DxCapture::getAdapters()
{
	int i = 0;
	IDXGIAdapter* adapterTmpContainer;
	std::vector<IDXGIAdapter*> adapters;

	while (factoryPtr->EnumAdapters(i, &adapterTmpContainer) == S_OK) {
		adapters.push_back(adapterTmpContainer);
		++i;
	}

	return adapters;
}

void DxCapture::capture()
{
	this->initIDXGIFactory();
	auto adaptorVector = this->getAdapters();

	DXGI_OUTDUPL_FRAME_INFO outInfo = {0};
	IDXGIResource* giResource = nullptr;

	

	//IDXGIOutputDuplication::AcquireNextFrame(frameTimeout, &outInfo, &giResource);
}

