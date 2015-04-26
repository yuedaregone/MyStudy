#include "MApplication.h"
#include "MyGraphics.h"
#include "MDirector.h"

void MApplication::mOnInit()
{
	appBeforLaunch();
	MWindow::mOnInit();
	SetWindowPos(m_hwnd, 0, 0, 0, 0, 0, SWP_SHOWWINDOW);//ʹ�ô�����������

	Gdiplus::GdiplusStartup(&m_gdiplusToken, &gdiplusStartupInput, NULL);//��ʼ��DGI
	g_mDirector->setWH(GetSystemMetrics(SM_CXSCREEN), GetSystemMetrics(SM_CYSCREEN));
	g_mDirector->setWnd(m_hwnd);
	g_mDirector->init();
	appLaunchFinish();
}

void MApplication::mOnDestroy()
{
	MWindow::mOnDestroy();
	Gdiplus::GdiplusShutdown(m_gdiplusToken);//ж��GDI
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