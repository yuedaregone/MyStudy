#include "Applegate.h"
#include "MDraw.h"
#include "MWindow.h"
#include "resource.h"

#define WIN32_LEAN_AND_MEAN
#define APP_WIDTH  300
#define APP_HEIGHT 300
int APIENTRY _tWinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPTSTR    lpCmdLine,
	_In_ int       nCmdShow)
{	 
	RECT rect;
	rect.left = 10;
	rect.bottom = g_mDirector->getScreenHeight() - 50;
	rect.right = APP_WIDTH;
	rect.top = rect.bottom - APP_HEIGHT;
	MApplicationProtocol* ap = new Applegate();
	MWindow mw;
	mw.registerApplication(ap);
	mw.mSetIcon(IDI_ICON1);
	mw.mSetTitle("Draw");
	mw.mSetRect(rect);
	mw.mRun(hInstance, nCmdShow);
	return 0;
}