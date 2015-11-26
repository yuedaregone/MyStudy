#pragma once
#include <windows.h>
#include "ImageMgr.h"
#include <gdiplus.h>
#include "MShap.h"
#include "MAction\MOpacityProtocol.h"
#include "MActionTarget.h"
using namespace Gdiplus;

class MAction;
class CC_DLL MyGraphics : public MActionTarget, public MOpacityProtocol
{
public:
	MyGraphics();
	~MyGraphics(){}
	
	void init(HWND _wnd);
	void update(float dt);
	void clear();
	void destroy();
public:
	Gdiplus::Graphics* getGraphics() { return m_graphics; }
	void drawLine(const MPoint& _p1, const MPoint& _p2) {};
	void drawImage(Image* _img, const MPoint& _p, const MSize& _s);
	MyGraphics* clone();
	MPoint convertPoint(MPoint& _point);
	void setClearColor(const MColor& _color) { m_clearColor = _color; }
	virtual void setOpacity(BYTE _alpha) { m_srcAlpha = _alpha; }
	virtual BYTE getOpacity() { return m_srcAlpha; }
	virtual void runAction(MAction* _action);
private:
	HDC m_dstDC;
	HWND m_wnd;
	ImageMgr m_imageMgr;
	HDC m_srcDC;
	HBITMAP m_bitMap;
	Graphics* m_graphics;
	int m_scecond;
	MColor m_clearColor;
	BYTE m_srcAlpha;
	BLENDFUNCTION m_Blend;
	POINT m_originPos;
private:
	void getCurTime(int &hour, int &minute, int &second);
	void DrawNum(int num, int _x, int _y, bool _isSec = false);
	void render();
};

