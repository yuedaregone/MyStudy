#ifndef __MAPPLICATION_H__
#define __MAPPLICATION_H__
#include "../win32/MWindow.h"
#include "MApplicationProtocol.h"
#include <gdiplus.h>
#include "MyGraphicsProtocol.h"

class MApplication : public MWindow, public MApplicationProtocol
{
public:
	MApplication() {};
	virtual ~MApplication() {};
private:
	ULONG_PTR m_gdiplusToken;
	Gdiplus::GdiplusStartupInput gdiplusStartupInput;
public:	
	virtual void mOnInit();
	virtual void mOnDestroy();
	virtual void mOnTimer();
	virtual void mOnMainLoop();		
	HWND getHWnd() { return m_hwnd; }
};

#endif