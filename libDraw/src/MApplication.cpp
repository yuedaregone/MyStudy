#include "MApplication.h"
#include "MyGraphics.h"
#include "MDirector.h"
#include "MTouchControl.h"

void MApplication::mOnInit(int x, int y, int w, int h)
{
	appBeforLaunch();
	SetWindowPos(m_hwnd, HWND_TOP, x, y, w, h, SWP_SHOWWINDOW);//使用窗口总在最上
	
	Gdiplus::GdiplusStartup(&m_gdiplusToken, gdiplusStartupInput, NULL);//初始化DGI
	g_mDirector->setWPos(x,y);
	mSetHW(w, h);
	g_mDirector->setWnd(m_hwnd);
	g_mDirector->init();
	appLaunchFinish();
}

void MApplication::mOnDestroy()
{
	Gdiplus::GdiplusShutdown(m_gdiplusToken);//卸载GDI
	//g_mDirector->destoy();
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

void MApplication::mSetEnd(bool _isEnd)
{
	MApplicationProtocol::mSetEnd(_isEnd);
	if (_isEnd)
	{
		::PostMessage(m_hwnd, WM_QUIT, 0, 0);
	}
}

void MApplication::mInvokeDragFile(const std::vector<std::string>& files)
{
	g_mDirector->invokeDraFileCallback(files);
}

bool MApplication::mTouchBegin(int x, int y)
{
	return g_mTouchControl->mTouchBegin(MPoint((float)x, (float)y));
}

void MApplication::mTouchMove(int x, int y)
{
	g_mTouchControl->mTouchMove(MPoint((float)x, (float)y));
}

void MApplication::mTouchEnd(int x, int y)
{
	g_mTouchControl->mTouchEnd(MPoint((float)x, (float)y));
}