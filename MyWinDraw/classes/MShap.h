#ifndef __MSHAP_H__
#define __MSHAP_H__
#include "MPlatform.h"
class MPoint
{
public:
	MPoint() : x(0.0f), y(0.0f){};
	MPoint(float _x, float _y) :x(_x), y(_y){};
	~MPoint(){};
	MPoint& operator=(const MPoint& _p)
	{
		this->x = _p.x;
		this->y = _p.y;
		return *this;
	}
	MPoint(const MPoint& _p) :x(_p.x), y(_p.y){};
	MPoint operator+(const MPoint& _p)
	{
		MPoint p;
		p.x = this->x + _p.x;
		p.y = this->y + _p.y;
		return p;
	}
public:
	float x;
	float y;
};

#define MPointZore MPoint(0.0f, 0.0f)
#define mp(x,y) MPoint(x,y)

class MSize
{
public:
	MSize() : w(0.0f), h(0.0f){};
	MSize(float _w, float _h) :w(_w), h(_h){};
	~MSize(){};
	MSize& operator=(const MSize& _s)
	{
		this->w = _s.w;
		this->h = _s.h;
		return *this;
	}
	MSize(const MSize& _s) :w(_s.w), h(_s.h) {};
public:
	float w;
	float h;
};

#define MSizeZore MSize(0.0f, 0.0f)
#define ms(w,h) MSize(x,y)

class MRect
{
public:
	MRect() : m_p(0.0f, 0.0f), m_s(0.0f, 0.0f){};
	MRect(float _x, float _y, float _w, float _h) :m_p(_x, _y), m_s(_w, _h){};
	~MRect(){};
	MRect& operator=(const MRect* _r)
	{
		this->m_p = _r->m_p;
		this->m_s = _r->m_s;
		return *this;
	}
	MRect(const MRect& _r) :m_p(_r.m_p), m_s(_r.m_s) {};
public:
	MPoint m_p;
	MSize m_s;
};

#define MRectZore MRect(0.0f, 0.0f, 0.0f, 0.0f)
#define mr(x,y,w,h) MRect(x,y,w,h)

class MColor
{
public:
	MColor() :m_a(255), m_r(255), m_g(255), m_b(255){};
	MColor(BYTE a, BYTE r, BYTE g, BYTE b) :m_a(a), m_r(r), m_g(g), m_b(b){};
	MColor(BYTE r, BYTE g, BYTE b) :m_a(255), m_r(r), m_g(g), m_b(b){};
	~MColor(){};
	MColor& operator=(const MColor& _color)
	{
		this->m_a = _color.m_a;
		this->m_r = _color.m_r;
		this->m_g = _color.m_g;
		this->m_b = _color.m_b;
		return *this;
	}
	MColor(const MColor& _color) :m_a(_color.m_a), m_r(_color.m_r), m_g(_color.m_g), m_b(_color.m_b){};
public:
	BYTE m_a;
	BYTE m_r;
	BYTE m_g;
	BYTE m_b;
};
#endif