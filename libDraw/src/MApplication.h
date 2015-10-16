#ifndef __MAPPLICATION_H__
#define __MAPPLICATION_H__
#include "MyDef.h"
#include "MWindow.h"
#include "MApplicationProtocol.h"
#include "MyGraphicsProtocol.h"

class MApplication : public MWindow, public MApplicationProtocol
{
public:
	MApplication() {};
	virtual ~MApplication() {};
private:
	ULONG_PTR m_gdiplusToken;
	Gdiplus::GdiplusStartupInput gdiplusStartupInput;	

	MyGraphicsProtocol* m_g;	
public:	
	virtual void mOnInit();
	virtual void mOnDestroy();
	virtual void mOnTimer();
	virtual void mOnMainLoop();		
	HWND getHWnd() { return m_hwnd; }
};

#endif