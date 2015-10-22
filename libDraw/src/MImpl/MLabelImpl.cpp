#include "MLabelImpl.h"
#include "MCommonFunction.h"
#include "MDirector.h"
#include <stdio.h>
#define SafeDelete(p) do {if (p) delete p;}while (0)

MLabelImpl::MLabelImpl()
	: m_g(NULL)
	, m_brush(NULL)
	, m_fFamily(NULL)
	, m_font(NULL)
	, m_isInit(false)
{
}

MLabelImpl::~MLabelImpl()
{	
	m_g = NULL;
	SafeDelete(m_brush);
	SafeDelete(m_fFamily);
	SafeDelete(m_font);
}

void MLabelImpl::init(MyGraphics* _g, uint _size, const MColor& _color)
{
	if (m_isInit)
		return;
	m_g = _g;
	m_brush = new Gdiplus::SolidBrush(Color(_color.m_a, _color.m_r, _color.m_g, _color.m_b));
	m_fFamily = new Gdiplus::FontFamily(L"Arial");
	m_font = new Gdiplus::Font(m_fFamily, (float)_size, FontStyleRegular, UnitPixel);
	m_isInit = true;
}

void MLabelImpl::setColor(const MColor& _color)
{
	m_brush->SetColor(Color(_color.m_a, _color.m_r, _color.m_g, _color.m_b));
}

void MLabelImpl::setSize(uint _size)
{
	SafeDelete(m_font);
	m_font = new Gdiplus::Font(m_fFamily, (float)_size, FontStyleRegular, UnitPixel);
}

void  MLabelImpl::setPosition(const MPoint& _p)
{
	MPoint point = _p;
	m_point = m_g->convertPoint(point);
}

void MLabelImpl::drawStr(const char* _str)
{
	int nLen = 0;
	wchar_t* wstr = cFunction::utf8ToUnicode(_str, nLen);
	m_g->getGraphics()->DrawString(wstr, nLen, m_font, Gdiplus::PointF(m_point.x, m_point.y), m_brush);
	delete[] wstr;
}