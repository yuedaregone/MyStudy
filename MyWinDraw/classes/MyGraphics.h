#pragma once
#include <windows.h>
#include "ImageMgr.h"
#include <gdiplus.h>
#include "MyGraphicsProtocol.h"
#include "MShap.h"
using namespace Gdiplus;

class MyGraphics : public MyGraphicsProtocol
{
public:
	MyGraphics(){}
	~MyGraphics(){}
	
	void init(HWND _wnd);
	void update();
	void clear();
	void destroy();
public:
	Gdiplus::Graphics* getGraphics() { return m_graphics; }
	void drawLine(const MPoint& _p1, const MPoint& _p2) {};
	void drawImage(Image* _img, const MPoint& _p, const MSize& _s);
	MyGraphics* clone();
	MPoint convertPoint(MPoint& _point);
private:
	HDC m_dstDC;
	HWND m_wnd;
	ImageMgr m_imageMgr;
	HDC m_srcDC;
	HBITMAP m_bitMap;
	Graphics* m_graphics;
	int m_scecond;
private:
	void getCurTime(int &hour, int &minute, int &second);
	void DrawNum(int num, int _x, int _y, bool _isSec = false);
	void render();
};

