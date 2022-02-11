#include "imageReader.h"


class imageReader
{

public:
	imageReader();
	~imageReader();

	HBITMAP readBuffer(char* buffer, HWND parentWindow, RECT rectDisp);
	void renderImage(HBITMAP disimage);

private:
	HWND parent;
	RECT rect;
	HBITMAP image;

};
imageReader::imageReader()
{

}
imageReader::~imageReader()
{

}
HBITMAP imageReader::readBuffer(char* buffer, HWND parentWindow, RECT rectDisp)
{
	parent = parentWindow;
	rect = rectDisp;

	BITMAPFILEHEADER& bfh = (BITMAPFILEHEADER&)buffer[0];
	BITMAPINFO& bi = (BITMAPINFO&)buffer[sizeof(BITMAPFILEHEADER)];
	BITMAPINFOHEADER& bih = bi.bmiHeader;
	char* bitmap = &buffer[bfh.bfOffBits];

	HDC hdcW = GetDC(parent); // window's DC
	image = CreateDIBitmap(hdcW, &bih, CBM_INIT, bitmap, &bi, DIB_RGB_COLORS);
	image = CreateResampledBitmap(hdcW, image, rect.right - rect.left, rect.bottom - rect.top, STOCK_FILTER_BOX);
	return image;
}

void imageReader::renderImage(HBITMAP disimage)
{
	PAINTSTRUCT ps;

	HDC hdc = BeginPaint(parent, &ps);
	BITMAP bm;
	HDC hdcMem = CreateCompatibleDC(hdc);
	SelectObject(hdcMem, disimage);
	GetObject(disimage, sizeof(bm), &bm);

	BitBlt(hdc, rect.left, rect.top, bm.bmWidth, bm.bmHeight, hdcMem, 0, 0, SRCCOPY);
	DeleteDC(hdcMem);

	EndPaint(parent, &ps);

}



// example of implementation of above class


//imageReader  imageobj;
// FILE* f = fopen( "C:\\test.bmp", "rb" ); if( f==0 ) return 1;
//  fread( buf, 1,sizeof(buf), f );
//  fclose(f);
//}

//  WINDOWPLACEMENT lpwndpl2;
//  GetWindowPlacement(hw,&lpwndpl2); //hw is handle to picture control where u want to render image
//  RECT rectImage;
//  rectImage.left=lpwndpl2.rcNormalPosition.left;
//  rectImage.right=lpwndpl2.rcNormalPosition.right;
//  rectImage.top=lpwndpl2.rcNormalPosition.top;
//  rectImage.bottom=lpwndpl2.rcNormalPosition.bottom;

//  HBITMAP hBitmap=imageobj.readBuffer(buf,hwparent,rectImage);//hwparent is handle to main dialog(parent)
/
//imageobj.renderImage(hBitmap);
//InvalidateRect(hwparent , &rectImage, TRUE);



// add imageobj.renderImage(hBitmap); in wm_paint