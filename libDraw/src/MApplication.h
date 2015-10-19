#ifndef __MAPPLICATION_H__
#define __MAPPLICATION_H__
#include "MyDef.h"
#include "MyGraphicsProtocol.h"
#include "MApplicationProtocol.h"
class MApplication : public MApplicationProtocol
{
public:
	MApplication() {};
	virtual ~MApplication() {};
private:
	ULONG_PTR m_gdiplusToken;
	Gdiplus::GdiplusStartupInput gdiplusStartupInput;	
public:	
	virtual void appBeforLaunch() = 0;
	virtual void appLaunchFinish() = 0;

	virtual void mOnInit(int x, int y, int w, int h);
	virtual void mOnDestroy();
	virtual void mOnTimer();
	virtual void mOnMainLoop(); 
	virtual void mSetHWND(void* _hwnd);

	void mSetHW(int _w, int _h);
private:
	HWND m_hwnd;
};

#endif