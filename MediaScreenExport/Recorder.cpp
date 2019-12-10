#include "pch.h"
#include "Recorder.h"

Recorder::Recorder() : frameSize((float)16.66), stop(false), a(0) {
}

Recorder::Recorder(float mframeSize) : frameSize(mframeSize), stop(false), a(0) {
}

void Recorder::Record() {
	Gdiplus::GdiplusStartupInput gdiplusStartupInput;
	GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, NULL);

	GetEncoderClsid(L"image/jpeg", &this->clsid);

	windowDc = GetDC(desktop);
	if (windowDc == NULL)
		throw 1;
	compatibleDc = CreateCompatibleDC(windowDc);
	SetStretchBltMode(compatibleDc, COLORONCOLOR);

	GetClientRect(desktop, &windowSize);

	bitmap = CreateCompatibleBitmap(windowDc, windowSize.right, windowSize.bottom);
	bi.biSize = sizeof(BITMAPINFOHEADER);
	bi.biWidth = windowSize.right;
	bi.biHeight = -windowSize.bottom;  //this is the line that makes it draw upside down or not
	bi.biPlanes = 1;
	bi.biBitCount = 32;
	bi.biCompression = BI_RGB;
	bi.biSizeImage = 0;
	bi.biXPelsPerMeter = 0;
	bi.biYPelsPerMeter = 0;
	bi.biClrUsed = 0;
	bi.biClrImportant = 0;

	buffer = new BYTE[bi.biSizeImage];

	/*while (!stop) {
		getScreenTexture();
	}*/
}

void Recorder::Shutdown()
{
	DeleteObject(bitmap);
	DeleteDC(windowDc);
	DeleteDC(compatibleDc);
	ReleaseDC(desktop, windowDc);

	Gdiplus::GdiplusShutdown(gdiplusToken);
}

HBITMAP Recorder::getScreenTexture() {
	SelectObject(compatibleDc, bitmap);
	StretchBlt(compatibleDc, 0, 0, windowSize.right, windowSize.bottom, windowDc, 0, 0, windowSize.right, windowSize.bottom, SRCCOPY); //change SRCCOPY to NOTSRCCOPY for wacky colors !
	GetDIBits(compatibleDc, bitmap, 0, windowSize.bottom, buffer, (BITMAPINFO*)&bi, DIB_RGB_COLORS);

	return bitmap;
	/*Gdiplus::Bitmap* bitmapObj = Gdiplus::Bitmap::FromHBITMAP(bitmap, NULL);
	saveBitmap(bitmapObj);

	delete bitmapObj;*/
}


int Recorder::GetEncoderClsid(const WCHAR* format, CLSID* pClsid)
{
	UINT  num = 0;          // number of image encoders
	UINT  size = 0;         // size of the image encoder array in bytes

	Gdiplus::ImageCodecInfo* pImageCodecInfo = NULL;

	Gdiplus::GetImageEncodersSize(&num, &size);
	if (size == 0)
		return -1;  // Failure

	pImageCodecInfo = (Gdiplus::ImageCodecInfo*)(malloc(size));
	if (pImageCodecInfo == NULL)
		return -1;  // Failure

	Gdiplus::GetImageEncoders(num, size, pImageCodecInfo);

	for (UINT j = 0; j < num; ++j)
	{
		if (wcscmp(pImageCodecInfo[j].MimeType, format) == 0)
		{
			*pClsid = pImageCodecInfo[j].Clsid;
			free(pImageCodecInfo);
			return j;  // Success
		}
	}

	free(pImageCodecInfo);
	return -1;  // Failure
}

void Recorder::saveBitmap(Gdiplus::Bitmap* bitmap)
{
	std::string concatName = (std::string("C:\\Lab\\toto\\a") + std::to_string(a++) + std::string("myimg.jpeg"));
	std::wstring inter = std::wstring(concatName.begin(), concatName.end());

	const WCHAR* name = inter.c_str();

	auto state = bitmap->Save(name, &clsid);

	if (state != Gdiplus::Ok) {
		std::cout << "gdi plus failed" << std::endl;
	}
}
