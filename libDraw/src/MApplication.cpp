#include "MApplication.h"
#include "MyGraphics.h"
#include "MDirector.h"

void MApplication::mOnInit(int x, int y, int w, int h)
{
	appBeforLaunch();
	SetWindowPos(m_hwnd, 0, x, y, w, h, SWP_SHOWWINDOW);//使用窗口总在最上
	
	Gdiplus::GdiplusStartup(&m_gdiplusToken, &gdiplusStartupInput, NULL);//初始化DGI
	g_mDirector->setWPos(x,y);
	mSetHW(w, h);
	g_mDirector->setWnd(m_hwnd);
	g_mDirector->init();
	appLaunchFinish();
}

void MApplication::mOnDestroy()
{
	Gdiplus::GdiplusShutdown(m_gdiplusToken);//卸载GDI
	g_mDirector->destoy();
}

void MApplication::mOnTimer()
{
	g_mDirector->onMainLoop();
}

void MApplication::mOnMainLoop()
{
	g_mDirector->onMainLoop();	
}

void MApplication::mSetHWND(void* _hwnd)
{
	m_hwnd = (HWND)_hwnd;
}

void MApplication::mSetHW(int _w, int _h)
{
	if (_h == -1 && _w == -1)
	{
		_w = GetSystemMetrics(SM_CXSCREEN); 
		_h = GetSystemMetrics(SM_CYSCREEN);
	}
	g_mDirector->setWH(_w, _h);
}