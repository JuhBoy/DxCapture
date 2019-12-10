#pragma once

#pragma comment( lib, "Gdiplus.lib" )
#include <windows.h>
#include <objidl.h>
#include <gdiplus.h>
#include <stdio.h>
#include <iostream>
#include <string>
#include <functional>

__declspec(dllexport) class Recorder
{
public:
	Recorder();
	Recorder(float frameSize);

	__declspec(dllexport) void Record();
	__declspec(dllexport) void Shutdown();
	__declspec(dllexport) HBITMAP getScreenTexture();

private:
	float frameSize;
	int a;
	bool stop;
	CLSID clsid;
	ULONG_PTR gdiplusToken;

	HDC windowDc, compatibleDc;
	HBITMAP bitmap;
	HWND desktop = GetDesktopWindow();
	BITMAPINFOHEADER  bi;
	LPBYTE buffer;

	RECT windowSize;

	int GetEncoderClsid(const WCHAR* format, CLSID* pClsid);
	void saveBitmap(Gdiplus::Bitmap* bitmap);
};

// ===========================
//	   DLL EXPORT PINVOKE
// ===========================
extern "C" __declspec(dllexport) Recorder * create_recorder() {
	return new Recorder();
};

extern "C" __declspec(dllexport) void Record(Recorder * recorder) {
	recorder->Record();
};

extern "C" __declspec(dllexport) void Shutdown(Recorder * recorder) {
	recorder->Shutdown();
}

extern "C" __declspec(dllexport) HBITMAP getScreenTexture(Recorder * recorder) {
	return recorder->getScreenTexture();
}
