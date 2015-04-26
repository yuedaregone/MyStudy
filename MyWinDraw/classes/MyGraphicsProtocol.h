#ifndef __MYGRAPHICSPROTOCOL_H__
#define __MYGRAPHICSPROTOCOL_H__

//typedef void (*SEL_Update)();
class MyWndDraw;
class MyGraphicsProtocol
{
public:
	virtual ~MyGraphicsProtocol() {}
	virtual void init(HWND _wnd) = 0;
	virtual void update() = 0;
	virtual void destroy() = 0;
};

#endif