#ifndef __MLABELIMPL_H__
#define __MLABELIMPL_H__
#include "MyGraphics.h"
#include "MShap.h"
#include <gdiplus.h>

class MLabelImpl
{
public:
	MLabelImpl();
	~MLabelImpl();
	void init(MyGraphics* _g, uint _size, const MColor& _color);
	void setColor(const MColor& _color);
	void setSize(uint _size);
	void setPosition(const MPoint& _p);
	void drawStr(const char* _str);
private:
	MyGraphics* m_g;
	Gdiplus::SolidBrush* m_brush;
	Gdiplus::FontFamily* m_fFamily;
	Gdiplus::Font* m_font;
	MPoint m_point;
	bool m_isInit;
};

#endif