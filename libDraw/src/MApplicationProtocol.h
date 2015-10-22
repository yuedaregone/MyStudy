#ifndef __MAPPLICATIONPROTOCOL_H__
#define __MAPPLICATIONPROTOCOL_H__
#include "MPlatform.h"
class CC_DLL MApplicationProtocol
{
public:
	virtual ~MApplicationProtocol(){};	
public:
	virtual void mOnInit(int x, int y, int w, int h) = 0;
	virtual void mOnDestroy() = 0;
	virtual void mOnTimer() = 0;
	virtual void mOnMainLoop() = 0;
	virtual void mSetHWND(void* _hwnd) = 0;	
};

#endif