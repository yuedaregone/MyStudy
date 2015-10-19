#include "MyGraphics.h"
#include <time.h> 
#include <windows.h>
#include "MDirector.h"


void MyGraphics::init(HWND _wnd)
{
	g_imageMgr->LoadMyImage(102, 112);
	m_wnd = _wnd;
	m_scecond = -1;

	m_dstDC = ::GetDC(m_wnd);
	m_srcDC = ::CreateCompatibleDC(m_dstDC);
	m_bitMap = ::CreateCompatibleBitmap(m_dstDC, g_mDirector->getWidth(), g_mDirector->getHeight());
	::SelectObject(m_srcDC, m_bitMap);
	m_graphics = new Graphics(m_srcDC);	
}

void MyGraphics::destroy()
{
	m_graphics->ReleaseHDC(m_srcDC);
	delete m_graphics;
	::ReleaseDC(m_wnd, m_dstDC);
	::DeleteDC(m_srcDC);
	::DeleteObject(m_bitMap);
}

void  MyGraphics::update()
{	
	//int hour, minute, second;
	//getCurTime(hour, minute, second);	
	//if (m_scecond != second)
	//{
		//m_graphics->Clear(Color(0, 0, 0, 0));
		//DrawNum(hour, 0, 0);
		//DrawNum(minute, 60, 0);
		//DrawNum(second, 120, 0, true);
	//return;
		render();
	//}	
}

void MyGraphics::clear()
{
	m_graphics->Clear(Color(255, 255, 255, 255));
}

void  MyGraphics::render()
{
	BLENDFUNCTION _Blend;
	_Blend.BlendOp = 0;
	_Blend.BlendFlags = 0;
	_Blend.AlphaFormat = 0.5;
	_Blend.SourceConstantAlpha = 255;

	RECT rect;
	GetWindowRect(m_wnd, &rect);

	POINT p = { rect.left, rect.top };
	POINT p1 = {0, 0};
	SIZE s = { rect.right - rect.left, rect.bottom - rect.top };
	//鼠标会穿透窗体中Alpha值为0的区域
	::UpdateLayeredWindow(m_wnd, m_dstDC, &p,
		&s, m_srcDC, &p1, 0, &_Blend, ULW_ALPHA);
}

MyGraphics* MyGraphics::clone()
{
	MyGraphics* g = new MyGraphics();
	g->init(m_wnd);
	return g;
}

MPoint MyGraphics::convertPoint(MPoint& _point)
{
	MPoint point = _point;
	g_mDirector->convertPointToGLPoint(point);
	return point;
}

void  MyGraphics::getCurTime(int &hour, int &minute, int &second)
{
	struct tm timeNow;
	time_t long_time;
	time(&long_time);
	localtime_s(&timeNow, &long_time);
	hour = timeNow.tm_hour;
	minute = timeNow.tm_min;
	second = timeNow.tm_sec;
}

void MyGraphics::DrawNum(int num, int _x, int _y, bool _isSec)
{	
	return;
	m_scecond = num;	
	int width = g_mDirector->getWidth();
	int height = g_mDirector->getHeight();
	int num1 = num / 10;
	int num2 = num % 10;
	Image* image1 = g_imageMgr->getImageByKey(num1);
	Image* image2 = g_imageMgr->getImageByKey(num2);
	m_graphics->DrawImage(image1, _x, _y, image1->GetWidth(), image1->GetHeight());
	m_graphics->DrawImage(image2, _x + 27, _y, image2->GetWidth(), image2->GetHeight());
}

void MyGraphics::drawImage(Image* _img, const MPoint& _p, const MSize& _s)
{
	m_graphics->DrawImage(_img, _p.x, _p.y, _s.w, _s.h);
}